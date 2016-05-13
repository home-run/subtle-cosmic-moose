/**************************************************************************
 * AUTHOR   : Jesse Mazzella
 * CLASS    : CS1D
 * DATE     : 04-20-2016
 * ASSIGN 13: Breadth First Search
 *************************************************************************/
#ifndef CS1D_ASSIGNMENT4_CIRCULAR_VECTOR_EXCEPTIONS_H
#define CS1D_ASSIGNMENT4_CIRCULAR_VECTOR_EXCEPTIONS_H

#include <string>

/**
* @class RuntimeException
* A generic runtime exception class.
* @author Jesse Mazzella
*/
class RuntimeException
{
public:
    /// Create a default RuntimeException
    RuntimeException()
    { errorMsg = "Runtime Error"; }

    /// Create a RuntimeException with a custom error message
    RuntimeException(const std::string &err)
    { errorMsg = err; }

    /**
    * @brief Return the error message to the client
    * @author Jesse Mazzella
    * @return The related error message as a string
    */
    std::string getMessage() const
    { return errorMsg; }

protected:
    std::string errorMsg; ///< The error message
};

/**
* @class IndexOutOfBounds
* An exception class for IndexOutOfBounds errors
* @author Jesse Mazzella
*/
class IndexOutOfBounds : public RuntimeException
{
public:

    /// Create an IndexOutOfBounds exception with a custom error message
    IndexOutOfBounds(const std::string &err) { errorMsg = err; }
};

#endif //CS1D_ASSIGNMENT4_CIRCULAR_VECTOR_EXCEPTIONS_H
