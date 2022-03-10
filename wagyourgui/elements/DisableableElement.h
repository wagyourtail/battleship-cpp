//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_DISABLEABLEELEMENT_H
#define BATTLESHIP_DISABLEABLEELEMENT_H


class DisableableElement {
    public:
        virtual void setDisabled(bool disabled) = 0;
        virtual bool isDisabled() = 0;
};


#endif //BATTLESHIP_DISABLEABLEELEMENT_H
