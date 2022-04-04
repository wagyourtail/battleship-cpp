//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_BASEPACKET_H
#define BATTLESHIP_BASEPACKET_H

#include <vector>

class BasePacket {
    private:
        int size;
    public:
        explicit BasePacket(int size) {
            this->size = size;
        }
        virtual char* serialize() = 0;
        virtual void deserialize() = 0;
        virtual int getSize() const {return size;};
};


#endif //BATTLESHIP_BASEPACKET_H
