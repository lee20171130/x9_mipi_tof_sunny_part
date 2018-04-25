#include <memory.h>
#include <common/CompUtils.hpp>

/// Functor to calculate the absolute difference between two types
/**
 * The generic version of this functor always throws.
 * It needs to be specialized for each supported type.
 */
template<typename T>
struct AbsDiff
{
    /// return type of functor
    using return_t = T;

    /**
     * Calculates the absolute difference between the arguments
     *
     * @return absolute difference
     */
    return_t operator() (T, T) const
    {
        throw "Please specialize this template!";
    }
};


template<>
struct AbsDiff<uint32_t>
{
    using return_t = uint64_t;

    return_t operator() (uint32_t rhs, uint32_t lhs) const
    {
        auto ret = static_cast<int64_t> (rhs) - static_cast<int64_t> (lhs);
        ret = ret > 0 ? ret : -ret;
        return static_cast<uint64_t> (ret);
    }
};


template<>
struct AbsDiff<float>
{
    using return_t = double;

    return_t operator() (float rhs, float lhs) const
    {
        return fabs (static_cast<double> (rhs) - static_cast<double> (lhs));
    }
};

/**
 * this class lists several information (e.g. mismatches, average error, invalid values)
 * amongst given data to be compared against each other
 */
template<typename T>
class ComparisonLog
{
public:
    /**
     * constructor
     *
     * @param refData reference data for comparison
     * @param calData calculated data for comparison
     * @param size size of the array element to be processed
     * @param flags flag map to be provided, used as a specific ignore list
     */
    ComparisonLog (const T *refData, const T *calData, size_t size, uint32_t *flags = nullptr) :
        m_size (size), m_flagCount (0), m_mismatchCount (0), m_totalMismatch (0), m_maxMismatch (0), m_minMismatch (0), m_maxPosition (0), m_minPosition (0)
    {
        m_newRefData.reset (new T[size]);
        m_newCalData.reset (new T[size]);
        std::copy_n (PMD_CHECKED_ITERATOR (refData, size), size, PMD_CHECKED_ITERATOR (m_newRefData.get(), size));
        std::copy_n (PMD_CHECKED_ITERATOR (calData, size), size, PMD_CHECKED_ITERATOR (m_newCalData.get(), size));

        for (uint32_t idx = 0; idx < size; ++idx)
        {
            if (flags != nullptr)
            {
                if (flags[idx])
                {
                    m_flagCount++;
                    m_newRefData[idx] = 0;
                    m_newCalData[idx] = 0;
                }
            }
        }
    }

    /**
      * destructor
      */
    ~ComparisonLog()
    {
    }

    /**
     * prints the number of flagged values amongst the given comparison data
     *
     * @return  returns the number of flagged values
     */
    uint32_t countFlags()
    {
        std::cout << "Flagged values:" << m_flagCount << std::endl;
        return m_flagCount;
    }

    /**
     * calculates and prints the number of invalid (NaN) values amongst the given comparison data
     *
     * @return number of invalid (NaN) values
     */
    uint32_t countNans()
    {
        uint32_t nanCount = 0;

        for (uint32_t idx = 0; idx < m_size; ++idx)
        {
            if ( (pmd_isNaNOrInfinity (m_newRefData[idx]) && pmd_isNaNOrInfinity (m_newCalData[idx])) ||
                    (std::numeric_limits<float>::infinity() == m_newRefData[idx] && (std::numeric_limits<float>::infinity() == m_newCalData[idx] ||
                            -1.f * std::numeric_limits<float>::infinity() == m_newCalData[idx])))
            {
                nanCount++;
            }
        }
        std::cout << "NaN count: " << nanCount << std::endl;

        return nanCount;
    }

    /**
     * calculates number of total mismatches as well as the maximum and minimum mismatch
     * that occured amongst the given comparison data
     *
     * @param singleThresh threshold value for single data comparison
     * @param limit number of allowed missmatches
     *
     * @return returns true if mismatches have been found, otherwise false
     */
    bool findMismatches (const T singleThresh = 0, uint32_t limit = 0)
    {
        m_mismatchCount = 0;
        m_totalMismatch = 0;

        using diff_t = typename AbsDiff<T>::return_t;
        m_maxMismatch = std::numeric_limits<diff_t>::lowest();
        m_minMismatch = std::numeric_limits<diff_t>::max();

        for (uint32_t idx = 0; idx < m_size; ++idx)
        {
            AbsDiff<T> diff;
            auto misMatch = diff (m_newCalData[idx], m_newRefData[idx]);

            if (misMatch > singleThresh)
            {
                m_mismatchCount++;

                if (misMatch > m_maxMismatch)
                {
                    m_maxMismatch = misMatch;
                    m_maxPosition = idx;
                }

                if (misMatch < m_minMismatch)
                {
                    m_minMismatch = misMatch;
                    m_minPosition = idx;
                }
            }
            m_totalMismatch += misMatch;
        }

        if (m_mismatchCount > limit)
        {
            EXPECT_LE (m_mismatchCount, limit);
            return true;
        }
        return false;
    }

    /**
     * prints number of total mismatches as well as the maximum and minimum mismatch
     * that occured amongst the given comparison data
     */
    void printMismatches()
    {
        if (m_mismatchCount > 0)
        {
            std::cout << "Mismatch count: " << m_mismatchCount << std::endl;
            std::cout << "Max mismatch: " << m_maxMismatch << " | Position: " << m_maxPosition << " | Ref. Value: " << m_newRefData[m_maxPosition] << " | Cal. Value: " << m_newCalData[m_maxPosition] << std::endl;
            std::cout << "Min mismatch: " << m_minMismatch << " | Position: " << m_minPosition << " | Ref. Value: " << m_newRefData[m_minPosition] << " | Cal. Value: " << m_newCalData[m_minPosition] << std::endl;
        }
    }

    /**
     * calculates and prints the average error amongst the given comparison data
     *
     * @param averageThresh threshold value for average error comparison
     *
     * @return average error
     */
    T calcAverageError (const T averageThresh = 0)
    {
        T averageErr = (T) (fabsf ( (float) m_totalMismatch) / (float) m_size);

        std::cout << "Average error: " << averageErr << std::endl;
        if (averageThresh != 0)
        {
            EXPECT_LE (averageErr, averageThresh);
        }

        return averageErr;
    }

private:
    size_t m_size; ///< size of array elements in m_newRefData or m_newCalData
    std::unique_ptr<T[]> m_newRefData; ///< data used as reference to be compared against, flagged values are replaced with 0
    std::unique_ptr<T[]> m_newCalData; ///< calculated data, flagged values are replaced with 0

    uint32_t m_flagCount; ///< number of flagged values
    uint32_t m_mismatchCount; ///< number of mismatches
    typename AbsDiff<T>::return_t m_totalMismatch; ///< sum of total mismatches
    typename AbsDiff<T>::return_t m_maxMismatch; ///< maximum mismatch
    typename AbsDiff<T>::return_t m_minMismatch; ///< minimum mismatch
    uint32_t m_maxPosition; ///< array position of the maximum mismatch
    uint32_t m_minPosition; ///< array position of the minimum mismatch
};

template<typename T>
struct Thresholds
{
    T singleThresh; ///< Threshold value for single data comparison
    T averageThresh; ///< Threshold value for average error comparison
    uint32_t limit; ///< Number of allowed missmatches
};

/**
* This class creates a threshold struct and is generally used by tests to make the construction more verbose
*/
template<typename T>
class ThresholdsBuilder
{
public:
    ThresholdsBuilder<T> &setAbsoluteThresh (T absThresh)
    {
        result.singleThresh = absThresh;
        return *this;
    }
    ThresholdsBuilder<T> &setRelativeThresh (T relThresh)
    {
        result.averageThresh = relThresh;
        return *this;
    }
    ThresholdsBuilder<T> &setMismatches (uint32_t mismatches)
    {
        result.limit = mismatches;
        return *this;
    }
    Thresholds<T> build()
    {
        return result;
    }
private:
    struct Thresholds<T> result;
};

/**
* Compares an array of equal length and two data types
* if absolute difference between each value is within
* the below a predefined single threshold value.
* Furthermore the total average error is calculated
* and verified with respect to a predefined threshold limit.
* If necessary a limit value can be defined to allow for a certain
* number of missmatches.
* Additionally a flag map can be provided, which needs to be of equal
* size as the arrays to be compared with. In this case, the compare
* operation ignores the flagged data values for the verification
* process.
*
* @param name Name definition assigned to the test message notification
* @param size Size of the array element to be processed
* @param refData Data used as referernce to be compared against
* @param calData Data calculated in a previous step to validated
* @param threshs threshold values
* @param flags Flag map to be provided, used as a specific ignore list.
*
* @return True if comparison criteria are met, else false.
*/
template <typename T>
inline bool compare (const std::string name,
                     const size_t size,
                     const T *refData,
                     const T *calData,
                     struct Thresholds<T> threshs = {0, 0, 0},
                     uint32_t *flags = nullptr)
{
    ComparisonLog<T> log (refData, calData, size, flags);
    auto mismatchesFound = log.findMismatches (threshs.singleThresh, threshs.limit);

    if (mismatchesFound)
    {
        std::cout << std::endl;
        std::cout << "Variable: " << name.c_str() << std::endl;

        log.printMismatches();
        log.countFlags();
        log.countNans();
        log.calcAverageError (threshs.averageThresh);

        std::cout << std::endl;
    }

    return !mismatchesFound;
}
