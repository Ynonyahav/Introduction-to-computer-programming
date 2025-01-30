#pragma once

#include "Matrix.h"
#include <string>
#include <ostream>

/**
 * @class MataMvidia
 * @brief Represents a multimedia movie with frames stored as matrices.
 */
class MataMvidia {

    std::string movieName; /**< The name of the movie */
    std::string author; /**< The author of the movie */
    Matrix* frames; /**< Pointer to an array of frames */
    int length; /**< The current length of the movie */
    int maxSize; /**< The maximum size allocated for frames */
    static const int EXPAND_RATE = 2; /**< The rate at which to expand the frames array */
    static const int DEFAULT_EXPAND_BASE = 10; /**< The base size for initial allocation of frames */

public:
    
    /**
     * @brief Constructs a MataMvidia object with the given parameters.
     * @param movieName The name of the movie.
     * @param author The author of the movie.
     * @param matrix A pointer to the initial frames matrix.
     * @param length The length of the movie.
     */
    MataMvidia(std::string movieName, std::string author, const Matrix* matrix, const int length);
    
    /**
     * @brief Copy constructor for MataMvidia.
     * @param movie The MataMvidia object to copy from.
     */
    MataMvidia(const MataMvidia& movie);
    
    /**
     * @brief Destructor for MataMvidia.
     */
    ~MataMvidia();

    /**
     * @brief Output stream operator for MataMvidia.
     * @param os The output stream.
     * @param movie The MataMvidia object to output.
     * @return The output stream with the movie's data.
     */
    friend std::ostream& operator<<(std::ostream& os, const MataMvidia& movie);

    /**
     * @brief Assignment operator for MataMvidia.
     * @param movie The MataMvidia object to assign from.
     * @return A reference to the assigned MataMvidia object.
     */
    MataMvidia& operator=(const MataMvidia& movie);
    
    /**
     * @brief Adds a Matrix to the movie's frames.
     * @param matrix The Matrix to add.
     * @return A reference to the updated MataMvidia object.
     */
    MataMvidia& operator+=(const Matrix& matrix);
    
    /**
     * @brief Concatenates another MataMvidia object to this one.
     * @param movie The MataMvidia object to concatenate.
     * @return A reference to the updated MataMvidia object.
     */
    MataMvidia& operator+=(const MataMvidia& movie);
    
    /**
     * @brief Accesses a frame by index.
     * @param index The index of the frame to access.
     * @return A reference to the frame at the specified index.
     */
    Matrix& operator[](int index);
    
    /**
     * @brief Accesses a frame by index (const version).
     * @param index The index of the frame to access.
     * @return A const reference to the frame at the specified index.
     */
    const Matrix& operator[](int index) const;
};

/**
 * @brief Concatenates two MataMvidia objects.
 * @param movie1 The first MataMvidia object.
 * @param movie2 The second MataMvidia object.
 * @return A new MataMvidia object that is the concatenation of movie1 and movie2.
 */
MataMvidia operator+(const MataMvidia& movie1, const MataMvidia& movie2);
