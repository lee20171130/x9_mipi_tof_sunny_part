/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <stdio.h>
#include <android/log.h>
#include <iostream>

//! A streambuf class for android logging.
/**
*   Androidbuf implements a streambuf that writes all
*   its contents via __android_log_write to the Android
*   log buffer and also via printf to stdout.
*/
class Androidbuf : public std::streambuf
{
public:

    //! Constructor initializes the internal buffer
    Androidbuf()
    {
        resetBuffer();
    }

private:
    //!handles overflows of the internal buffer
    /**
    *   This method handles overflows by calling sync to flush the buffer.
    *   It handles EOF as needed.
    *   \param c Character that caused the overflow. If c is EOF it writes EOF to Androidbuf::pptr
    *   \return EOF if the sync succeeds, c or NOTEOF otherwise.
    */
    virtual int overflow (int c) override
    {
        const int OVERFLOWSUCCESS = traits_type::not_eof (c);
        auto result = this->sync() == SYNCSUCCESS ? OVERFLOWSUCCESS : OVERFLOWFAIL;
        if (result == OVERFLOWSUCCESS && c != traits_type::eof())
        {
            *this->pptr() = traits_type::to_char_type (c);
            this->pbump (1);
        }
        return result;
    }

    //! writes internal buffer into android log and to stdout
    /**
    *   This method writes the content of the internal buffer via __android_log_write to the Android
    *   log buffer and also via printf to stdout, resets the buffer and returns the number of chars written.
    *   \return number of chars written.
    */
    virtual int sync() override
    {
        int rc = SYNCSUCCESS;
        if (!isEmpty())
        {
            rc = writeBuffer() ? SYNCSUCCESS : SYNCFAIL;
            resetBuffer();
        }
        return rc;
    }

    //! writes buffer via __android_log_write and printf
    /**
    * \return true if both writes were successful, false otherwise
    */
    bool inline writeBuffer ()
    {
        buffer[contentSize()] = '\0';
        auto success = __android_log_write (ANDROID_LOG_INFO, "spectre info", buffer) > 0;
        success = success && printf ("%s", buffer) > 0;
        return success;
    }

    //! returns true if buffer is empty
    /** \return true if buffer is empty, false otherwise.
    */
    bool inline isEmpty() const
    {
        return this->pbase() == this->pptr();
    }

    //! delivers the number of unwritten bytes inside buffer
    /**
    * \return The number of unwritten bytes in buffer
    */
    size_t inline contentSize() const
    {
        return this->pptr() - this->pbase();
    }

    enum { bufsize = 128 }; // ... or some other suitable buffer size

    //! reset buffer to empty state
    void inline resetBuffer ()
    {
        this->setp (buffer, buffer + bufsize);
    }

    //! The internal buffer.
    char buffer[bufsize + 1]; // increase buffersize by one to ensure that we can always add a null byte
    constexpr static int SYNCSUCCESS = 0;
    constexpr static int SYNCFAIL = -1;
    constexpr static int OVERFLOWFAIL = traits_type::eof();
};

//! on Android OutRedirector redirects the output of cout and cerr, everywhere els it does nothing.
/*  OutRedirector redirects cout and cerr by creating Androidbuf objects and setting
*   them as streambuf of cout and cerr respectively. OutRedirector implements the RAII design pattern
*   and resets cout and cerr to there old buffers when deleted. The class is movable but not copyable.
*
*/
class OutRedirector
{
public:
    //! redirects the output of cout and cerr
    OutRedirector() :
        coutbuf (std::cout.rdbuf (new Androidbuf())),
        cerrbuf (std::cerr.rdbuf (new Androidbuf()))
    {
    }

    //! removes the redirection of cout and cerr
    ~OutRedirector()
    {
        coutbuf = std::cout.rdbuf (coutbuf);
        cerrbuf = std::cerr.rdbuf (cerrbuf);
        delete coutbuf;
        delete cerrbuf;

    }

    OutRedirector (const OutRedirector &other) = delete;  // non construction-copyable
    OutRedirector (OutRedirector &&) = default;  // construction-movable
    OutRedirector &operator= (const OutRedirector &) = delete; // non copyable
    OutRedirector &operator= (OutRedirector &&) = default;  // movable

private:
    std::streambuf *coutbuf;
    std::streambuf *cerrbuf;
};

//! returns an OutRedirector
/** On Android the returned OutRedirector will redirect cout and
*   cerr to the Android log and stdout. On every other system it will
*   just do nothing.
*   \return The OutRedirector object.
*/
inline OutRedirector redirectStdOutIfNecessary()
{
    return OutRedirector();
};

//! printf-like function to print log informations.
/** function to print out log strings.
*   On Android pmd_printf forwards the given parameters to
*   __android_log_print and printf.
*   On every other system it uses only printf.
*   \param format A printf-like format string.
*   \param args... 0 to n additional parameters, depending on the format string.
*   \return On success, the total number of characters written is returned.
*   If a writing error occurs, the error indicator (ferror) is set and a
*   negative number is returned.
*   \sa <a href="http://www.cplusplus.com/reference/cstdio/printf/">printf documentation</a>
*/
template<class... Args >
inline int pmd_printf (const char *format, Args &&... args)
{
    int result = printf (format, args...);
    if (result >= 0)
    {
        result = __android_log_print (ANDROID_LOG_INFO, "spectre info", format, args...);
    }
    return result;
}

inline int pmd_printf (const char *message)
{
	return pmd_printf("%s", message);
}
