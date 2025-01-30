#pragma once

#include <functional>
#include <unordered_map>
#include <string>

#include "Player.h"

using std::function;
using std::unique_ptr;
using std::unordered_map;
using std::string;


namespace playerfactory {

    // For easier readability, hopefully...
    using JobCreator = function<unique_ptr<Job>()>;
    using CharacterCreator = function<unique_ptr<Character>()>;
    /**
     * Factory class for creating players. (Singleton)
     */
    class PlayerFactory {
        unordered_map<string, JobCreator> m_jobCreators;
        unordered_map<string, CharacterCreator> m_characterCreators;
        // Private constructor to prevent instantiation. (Singleton)
        PlayerFactory();
        // Destructor.
        ~PlayerFactory() = default; // Optional but advised

    public:
        /**
         * Gets the singleton instance of the PlayerFactory.
         * @return The singleton instance of the PlayerFactory by reference.
         */
        static PlayerFactory& getInstance();
        // Deleted copy constructor. (Singleton)
        PlayerFactory(const PlayerFactory&) = delete;
        // Deleted copy assignment operator. (Singleton)
        PlayerFactory& operator=(const PlayerFactory&) = delete;

        /**
         * Creates a job of the given type.
         * @param type The type of the job to create.
         * @return A unique pointer to the created job.
         */
        unique_ptr<Job> createJob(const string& type) const;
        /**
         * Creates a character of the given type.
         * @param type The type of the character to create.
         * @return A unique pointer to the created character.
         */
        unique_ptr<Character> createCharacter(const string& type) const;

        /**
         * Registers a job creator with the given type.
         * @param type The type of the job to register.
         * @param jobCreator The job creator to register.
         */
        void registerJob(const string& type, JobCreator jobCreator);
        /**
         * Registers a character creator with the given type.
         * @param type The type of the character to register.
         * @param characterCreator The character creator to register.
         */
        void registerCharacter(const string& type, CharacterCreator characterCreator);
    };
}

