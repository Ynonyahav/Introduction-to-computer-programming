
#include "MataMvidia.h"


//****************************************************************************//

//Not on class demands
//MataMvidia::MataMvidia() : frames(nullptr), length(0), maxSize(0) {}

//****************************************************************************//

MataMvidia::MataMvidia(std::string  movieName,
                       std::string  author,
                       const Matrix* matrix, const int length) :
    movieName(std::move(movieName)),
    author(std::move(author)),
    frames(new Matrix[length]),
    length(length),
    maxSize(length) {
    for (int i = 0; i < length; i++) {
        frames[i] = matrix[i];
    }
}

//****************************************************************************//

MataMvidia::MataMvidia(const MataMvidia& movie) :
    movieName(movie.movieName),
    author(movie.author),
    frames(new Matrix[movie.maxSize]),
    length(movie.length),
    maxSize(movie.maxSize) {
    for (int i = 0; i < length; i++) {
        frames[i] = movie.frames[i];
    }
}

//****************************************************************************//

MataMvidia::~MataMvidia() {
    delete[] frames;
}

//****************************************************************************//

std::ostream& operator<<(std::ostream& os, const MataMvidia& movie) {
    os << "Movie Name: " << movie.movieName << std::endl;
    os << "Author: " << movie.author << std::endl;
    for (int i = 0; i < movie.length; i++) {
        os << std::endl << "Frame " << i << ":" << std::endl;
        os << movie.frames[i];
    }
    os << std::endl << "-----End of Movie-----" << std::endl;
    return os;
}

//****************************************************************************//

MataMvidia& MataMvidia::operator=(const MataMvidia& movie) {
    if (this != &movie) { //&& *this != movie), but no ==,!=  demand for class
        movieName = movie.movieName;
        author = movie.author;
        if (length != movie.length || maxSize != movie.maxSize) {
            delete[] frames;
            frames = new Matrix[movie.maxSize];
            length = movie.length;
            maxSize = movie.maxSize;
        }
        for (int i = 0; i < length; i++) {
            frames[i] = movie.frames[i];
        }
    }
    return *this;
}

//****************************************************************************//

MataMvidia& MataMvidia::operator+=(const Matrix& matrix) {
    if (maxSize <= length) {
        const Matrix* temp = frames;
        maxSize = EXPAND_RATE * (length ? length : DEFAULT_EXPAND_BASE);
        frames = new Matrix[maxSize];
        for (int i = 0; i < length; i++) {
            frames[i] = temp[i];
        }
        delete[] temp;
    }
    frames[length] = matrix;
    length += 1;
    return *this;
}

//****************************************************************************//

MataMvidia& MataMvidia::operator+=(const MataMvidia& movie) {
    for (int i = 0; i < movie.length; i++) {
        *this += movie.frames[i];
    }
    return *this;
}

//****************************************************************************//

MataMvidia operator+(const MataMvidia& movie1, const MataMvidia& movie2) {
    MataMvidia result(movie1);
    return result += movie2;
}

//****************************************************************************//

Matrix& MataMvidia::operator[](const int index) {
    if (index < 0 || index >= length) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return frames[index];
}

//****************************************************************************//

const Matrix& MataMvidia::operator[](const int index) const {
    if (index < 0 || index >= length) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return frames[index];
}


