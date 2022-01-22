#ifndef COMMONS_H
#define COMMONS_H

#define BLOCKWIDTH 50
#define BLOCKHEIGHT 40
#define MAXACC 5
#define DECEL 0.2f
#include <vector>

#define DEBUG

 
 enum class DIRDEP {LEFT,RIGHT,UP,DOWN,NONE};

 enum COLDIR { TOP =3, BOTTOM=2 , LEFT =0,RIGHT=1 };

enum ACTION {ND,DEL,NEXTLEVEL,CANSHOOT,JUMP};
#endif
