#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <string>
#include <iostream>

class Logger {
    private:
        //std::ostream m_outStream;

    public:
        Logger();
        ~Logger();

        void Write(std::string out) const;
        void WriteLine(std::string outLine) const;
        void WriteError(std::string errorMessage) const;
        void WriteCommandNotFound(std::string unknownCommand) const;
        void WriteHelp(unsigned int gameState) const;
};

#endif // _LOGGER_HPP_
