//
// Created by Artem on 25.01.2022.
//

#ifndef ORANGECOMPILETEST_ECHO_SERVER_HPP
#define ORANGECOMPILETEST_ECHO_SERVER_HPP
class echo_handler : public server::handler {
    void on_message(connection_ptr con, std::string msg) {
        con->write(msg);
    }
};
#endif //ORANGECOMPILETEST_ECHO_SERVER_HPP
