//
// Created by Marcin on 04.04.2019.
//

#ifndef SERVER_STOPPABLETHREADARGS_H
#define SERVER_STOPPABLETHREADARGS_H


class StoppableThreadArgs {
public:
    StoppableThreadArgs(bool &);
    bool &stopCond;
};


#endif //SERVER_STOPPABLETHREADARGS_H
