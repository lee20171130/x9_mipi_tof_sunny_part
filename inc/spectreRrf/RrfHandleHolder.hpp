/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __RRFHANDLEHOLDER_HPP__
#define __RRFHANDLEHOLDER_HPP__

#include <record/RRFReader.h>
#include <record/RRFWriter.h>

#include <string>

namespace spectre
{
    namespace rrfLib
    {
        /// RAI class for RRF handles
        struct RrfHandleHolder
        {
            /**
             * Ctor
             *
             * Opens a RRF in read-file mode
             *
             * @param file file name
             *
             */
            RrfHandleHolder (const std::string &file)
                : input (true)
            {
                if (royale_open_input_file (&handle, file.c_str()) != RRF_NO_ERROR)
                {
                    throw "Could not open input file";
                }
            }

            /**
             * Ctor
             *
             * Opens a RRF in write-file mode
             *
             * @param outFile file name for output
             * @param fileInfo fileInfo struct to write
             *
             */
            RrfHandleHolder (const std::string &outFile, const royale_fileinformation_v3 *fileInfo)
                : input (false)
            {
                if (royale_open_output_file (&handle, outFile.c_str(), fileInfo) != RRF_NO_ERROR)
                {
                    throw "Could not open output file";
                }
            }

            ~RrfHandleHolder()
            {
                if (input)
                {
                    royale_close_input_file (handle);
                }
                else
                {
                    royale_close_output_file (handle);
                }
            }

            operator royale_rrf_handle()
            {
                return handle;
            }

            operator const royale_rrf_handle() const
            {
                return handle;
            }


            royale_rrf_handle handle;
            bool input;
        };
    }
}
#endif /*__RRFHANDLEHOLDER_HPP__*/
