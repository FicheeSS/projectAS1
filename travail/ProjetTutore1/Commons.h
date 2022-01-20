#ifndef COMMONS_H
#define COMMONS_H

#define BLOCKWIDTH 50
#define BLOCKHEIGHT 40
#define MAXACC 5
#define DECEL 0.2f
#include <vector>

//#define DEBUG
 
 enum class DIRDEP {LEFT,RIGHT,UP,DOWN,NONE};

 enum COLDIR { TOP =0, BOTTOM=1 , LEFT =2,RIGHT=3 };

enum ACTION {ND,DEL,NEXTLEVEL};
#endif
