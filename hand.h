#ifndef _HAND_H
#define _HAND_H

unsigned int hand_width = 200;
unsigned int hand_height = 53;

char hand_image[] = 
"????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????"
"????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????"
"????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????"
"????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????"
"????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????"
"???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????y:--+d???????????????????????????????????????????????????????"
"????????????????????????????????????????????????????????????N?h???????????????????????????????????????????????????????????????????????????d-:::::???????????????????????????????????????????????????????"
"?????????????????????????????????????????????????????????\?\?//---:s?????????????????????????????????????????????????????????????????????????d----::s??????????????????????????????????????????????????????"
"??????????????????????????????????????????????????yoyd???d-`.-::o??????????????????????????????????????????????????????????????????????????:/::/::d?????????????????????????????????????????????????????"
"????????????????????????????????????????????????o..---N?s----::/N??????????????????????????????????????????????????????????????????????????o/:::::s?????????????????????????????????????????????????????"
"?????????????????????????????????????????????No-..-::s?y-:::://h??????????????hyy??????????????????????????????????????????????????????????y:::::::N????????????????????????????????????????????????????"
"???????????????????????????????????????????\?\?//.---://Nd-::/://y?????????????s----/N????????????????????????????????????????hhdN????????????h-::::::oyyhhdN??????????????????????????????????????????????"
"????????????????????????????????????????????s-:::::o?d:-:////+???????????Ny--:::/:N??????????????????????????????????????d-...:+h??????????y:::::::--...-:oN????????????????????????????????????????????"
"???????????????????????????????????????????o--::::/N?:-:::://d?????????\?\?//-:::///d???????????????????????????????????????y-------s?????????s///////::-..---+N???????????????????????????????????????????"
"????????????????????????????????????NdyhN\?\?//::::::o?y/++/////N?????????h:-://///h????????????????????????????????????????N/::-----+????????N/++++++/s:-:://:o???????????????????????????????????????????"
"??????????????????????????????????y+:--:o?N++++///s?o++oo++/y????????d/-://///+???????????????????????????????????????????No::-::::/y?????\?\?//+++++//ho////+++???????????????????????????????????????????"
"????????????????????????????????h:..--:/h??+o++++/hN+oo++++/N???????o:::///+/yN???????????????????????????????????????????\?\?///+++//::s??????o+o++++/ho/+//+++???????????????????????????????????????????"
"????????????????????????????????s:::-:+????oooo++/hh+ooo+++/?????Ny///++/++/h???????????????????????????????????????????????d/++++/:/:oN????oooo++++h+/+//+++???????????????????????????????????????????"
"????????????????????????????????o++/:::d???ooo++++yyoo+ooo+o?????+://+++++:d?????????????????????????????????????????????????y++o+/////+????oosoo++++:/++/+++?dssyhdN???????????????????????????????????"
"????????????????????????????????h+o+/:::y??ooo++++/+oooooo++??Ny//++++++++sN??????????????????????????????????????????????????h/+oo+/////d?d/+sso+++/-/++/++/+---://+???????????????????????????????????"
"????????????????????????????????Nyoo+//:/ysooo+++/+oo+++oo+:+o//+++++++/oN?????????????????????????????????????????????????????d/ooo+/////+--/oo+//++:/++//+::--://+/???????????????????????????????????"
"?????????????????????????????????d/++///::/oo++++/+oo+/+o+/:::/+++++++/y????????????????????????????????????????????????????????++ooo+////:::/+++///+//////+:--:///+/???????????????????????????????????"
"??????????????????????????????????o+++/:::/++++++/++o+++++//::////++++h?????????????????????????????????????????????????????????\?\?//ooo+//:::///+++/+++/////+/::::///o???????????????????????????????????"
"???????????????????????????????????+++/////+++++++++++++++///////++++N????????????????????????????????????????????????????????????o/oo++/://////++++///////+//:::///s???????????????????????????????????"
"???????????????????????????????????+++++//+++++++++++++++//++///+++:o????N?????????????????????????????????????????????????????????o+oo++///////+++/+/++///++///////h???????????????????????????????????"
"??????????????????????????????????h/++++++++o++++++++++++/+++/++++/s????d/-:sN????????????????????????????????????????????????????N?/+ooo++/////+++/+++++/++++/+++//h???????????????????????????????????"
"??????????????????????????????????o/++++o+ooo++++++++++++++/+++++//?????+----oN????????????????????????????????????????????????s--+s/++++++o++//+++/++++++++//++++//N???????????????????????????????????"
"??????????????????????????????????o+++++oo++o++ooo+++oo+o+++++////o????h::----/????????????????????????????????????????????Nh/.-:///-/++++++o+//++++/+++++++/++++///N???????????????????????????????????"
"?????????????????????????????????N/+++++oo+oo+++oo++++oo++o+++/////????y:----:::o?????????????????????????????????????????N+-----://:/++++++++//+++//+++++++/++++//:N???????????????????????????????????"
"?????????????????????????????????h/+++++ooooo+++o++++++++++++++////s??s-.--::///:N????????????????????????????????????????h::--..--::+++++++++++/+++++++++++/o++++//????????????????????????????????????"
"?????????????????????????????????o++++++oooo++++++++o++++++++++////:+/..-::////+??????????????????????????????????????????N//:-...--/+o++++++++oo++++++o++++/++//+//h???????????????????????????????????"
"???????????????????????????????\?\?//+++++++ooo+++++++o++oo++++++++//++/:::://+//s????????????????????????????????????????????d/:-----/+oo+++oooo+ooo++++++oo+++++++///+???????????????????????????????????"
"???????????????????????????????\?\?//+++o+++oo+++++++o++o+++++++++++++///:://+/+d??????????????????????????????????????????????h://////++ooo+++o+++ooo+++//++++++//////s???????????????????????????????????"
"???????????????????????????????\?\?//+/+++++oo+++++++++oo+++++++++++++/://///+hN????????????????????????????????????????????????o+o+++++ooooo++o+++++++/////++++++++///????????????????????????????????????"
"?????????????????????????????????s///+++++o+++++++ooo++++++++o++++///////+N???????????????????????????????????????????????????s+++++ooooooooooo+++++++///++++++////:N???????????????????????????????????"
"?????????????????????????????????o:::///++++++++++oo++++++++++++++++///+h??????????????????????????????????????????????????????do/+++o+oooooooo++++++++/++++++/////:????????????????????????????????????"
"????????????????????????????????N::---:/+++++++++++++++o++++++++++//oh????????????????????????????????????????????????????????????s++++++ooooooo++++/+++///++++////:h???????????????????????????????????"
"????????????????????????????????d----:::/+++++++++++++++++++++/:+sd?????????????????????????????????????????????????????????????????y//++oooooooo++++++++//++++///::/N??????????????????????????????????"
"????????????????????????????????o:///////+++++++++oo+++++++//ohN???????????????????????????????????????????????????????????????????????s/++ooooooo+++++++++++++/////:/N?????????????????????????????????"
"???????????????????????????????d:/++++++++++++++++oo++++/ohd?????????????????????????????????????????????????????????????????????????????dy+++ooooo+++++++++++++////+/oh????????????????????????????????"
"?????????????????????????????i\?\?///+++++++++++++++++++++/y???????????????????????????????????????????????????????????????????????????????????hy/++ooo++++//+++//+++//+++/o????????????????????????????????"
"??????????????????????????????y://++++++++++++++++++//od?????????????????????????????????????????????????????????????????????????????????????yo/+oooo+++++++////+++/////y???????????????????????????????"
"?????????????????????????????h://///+++++/++++++++++/??????????????????????????????????????????????????????????????????????????????????????????h:+oooo++++/+//++/++//////yN?????????????????????????????"
"???????????????????????????\?\?//:////++//+++++++++++++y???????????????????????????????????????????????????????????????????????????????????????????No+oooo+++++++++///++/////d?????????????????????????????"
"???????????????????????????d/:::////////+++++++++++N?????????????????????????????????????????????????????????????????????????????????????????????hy+oooo+++++++////+++/+///y????????????????????????????"
"??????????????????????????d/::::////////+++o++oo++dN???????????????????????????????????????????????????????????????????????????????????????????????y/oooooo+++++++/+++++++//y???????????????????????????"
"?????????????????????????h::::::////////++oooo++/h?????????????????????????????????????????????????????????????????????????????????????????????????Ny/+oooooo++++++++++/+++//d??????????????????????????"
"????????????????????????h::::://///////+++oo++++o???????????????????????????????????????????????????????????????????????????????????????????????????Ny++ooo++++++++++++++++++/d?????????????????????????"
"???????????????????????s:::::://////++++++o+++++N?????????????????????????????????????????????????????????????????????????????????????????????????????y+ooo+++++++++++++++++///?????????????????????????"
"??????????????????????o::::::////////++++ooo++/s??????????????????????????????????????????????????????????????????????????????????????????????????????N++ooo++++++++++++++++++/+d???????????????????????"
"???????????????????\?\?//::::://////+/+++++ooo++++d??????????????????????????????????????????????????????????????????????????????????????????????????????\?\?//+oooo+++++++++/++++++++/hN?????????????????????"
"???????????????????Ny:::::////////++++++ooo++/y?????????????????????????????????????????????????????????????????????????????????????????????????????????o+ooooooo++++++//++++++++/+?????????????????????"
"???????????????????y::::://///////+++++ooo++++?????????????????????????????????????????????????????????????????????????????????????????????????????????\?\?//+oooooooo+++++/+/+++++++/o????????????????????";

#endif
