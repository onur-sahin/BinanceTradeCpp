#pragma once

#include <stdexcept>
#include <string>


class DatabaseException : public std::runtime_error {
public:
    explicit DatabaseException(const std::string &message)
    : std ::runtime_error("Database error: " + message){}
};


class DatabaseTableCreationException : public DatabaseException {
public:
    explicit DatabaseTableCreationException(const std::string &message)
    : DatabaseException("Table Creation Error: " + message){}
};