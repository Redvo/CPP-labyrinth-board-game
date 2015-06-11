/****************************************************************************************
 * Project in course The C++ Programming Language, 2014/2015
 * Authors: Irena Talašová (xtalas04@stud.fit.vutbr.cz)
 *          Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
 * File: treasurecard.h
 * Description: This header file contains class TreasureCard which holds methods and
 *              properties of object describing single trasure card.
 ***************************************************************************************/

#ifndef TREASURECARD_H
#define TREASURECARD_H

#include <types.h>

//! Class TreasureCard
/*!
This header file contains class TreasureCard which holds methods and 
properties describing object of single trasure card.
*/

class TreasureCard
{
    public:
		//! Constructor of treasure card object.
		/*!
			\param	cardNumber numeric identificator of new treasure card.
		*/
        TreasureCard(Treasure cardNumber);
        //! Destructor of treasure card object.
        ~TreasureCard();
        //! Getter for trasure card identificator.
		/*!
			\return	The numeric identificator of this treasure cart object.
		*/
        Treasure GetCardNumber();

    private:
        Treasure cardNumber; /*!< Numeric identificator of treasure card object. */ 
};

#endif // TREASURECARD_H

/* End of file treasurecard.h */