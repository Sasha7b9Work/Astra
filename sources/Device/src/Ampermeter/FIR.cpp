// 2022/11/15 16:06:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Ampermeter/FIR.h"


/*
    Filter type: Low Pass
    Filter model: Chebyshev
    Filter order: 2
    Sampling Frequency: 4 KHz
    Cut Frequency: 1.000000 KHz
    Pass band Ripple: 1.000000 dB
    Coefficents Quantization: float
    
    Z domain Zeros
    z = -1.000000 + j 0.000000
    z = -1.000000 + j 0.000000
    
    Z domain Poles
    z = -0.032032 + j -0.559413
    z = -0.032032 + j 0.559413
*/


int FIR::Step(int new_sample)
{
#define Ntap 511

    static const float FIRCoef[Ntap] = {
        0.00000086824106715644,
        0.00002929964100726002,
        -0.00000260501350470779,
        -0.00002939810431896130,
        0.00000434262703858279,
        0.00002956209972511065,
        -0.00000608159587253740,
        -0.00002979150876567423,
        0.00000782243590067508,
        0.00003008614585811939,
        -0.00000956564174931897,
        -0.00003044573036866177,
        0.00001131162710555502,
        0.00003086992995040929,
        -0.00001306073523684171,
        -0.00003135837193615882,
        0.00001481327533687927,
        0.00003191058266728210,
        -0.00001656947867232582,
        -0.00003252597288626216,
        0.00001832944259810734,
        0.00003320388882078312,
        -0.00002009316301406014,
        -0.00003394359693044321,
        0.00002186055955460343,
        0.00003474421002319449,
        -0.00002363140558740922,
        -0.00003560469666339449,
        0.00002540528775991868,
        0.00003652393131570097,
        -0.00002718166024205022,
        -0.00003750064106009200,
        0.00002895984119341026,
        0.00003853333195013365,
        -0.00003073891990641706,
        -0.00003962032963259452,
        0.00003251774843017896,
        0.00004075980768884570,
        -0.00003429500440115735,
        -0.00004194969228433489,
        0.00003606914062164350,
        0.00004318761060007382,
        -0.00003783828739467259,
        -0.00004447095524544860,
        0.00003960028723990231,
        0.00004579686342067475,
        -0.00004135273921219533,
        -0.00004716209138430897,
        0.00004309289614313631,
        0.00004856300467571614,
        -0.00004481759258468633,
        -0.00004999563902841731,
        0.00004652331722088406,
        0.00005145561039465569,
        -0.00004820620748058719,
        -0.00005293798814064407,
        0.00004986191276068639,
        0.00005443733115479129,
        -0.00005148557821149205,
        -0.00005594770529247710,
        0.00005307192896583540,
        0.00005746252757465475,
        -0.00005461519652529477,
        -0.00005897447529284060,
        0.00005610898842325228,
        0.00006047554891746109,
        -0.00005754634036147779,
        -0.00006195701285256519,
        0.00005891977109462683,
        0.00006340920810261755,
        -0.00006022114712826031,
        -0.00006482152629021780,
        0.00006144160351499846,
        0.00006618246148578504,
        -0.00006257164222387489,
        -0.00006747946810776714,
        0.00006360111441317727,
        0.00006869879735499293,
        -0.00006451905237185399,
        -0.00006982553750434514,
        0.00006531366047322778,
        0.00007084361039721578,
        -0.00006597239912530587,
        -0.00007173557244691127,
        0.00006648186394991408,
        0.00007248251890106898,
        -0.00006682761805924579,
        -0.00007306414755741382,
        0.00006699422409351832,
        0.00007345865882618404,
        -0.00006696523428897633,
        -0.00007364253409666541,
        0.00006672296548535658,
        0.00007359049584651454,
        -0.00006624835394204421,
        -0.00007327550230351805,
        0.00006552096644579134,
        0.00007266851482927465,
        -0.00006451885308520020,
        -0.00007173825863247955,
        0.00006321827266844918,
        0.00007045115232245183,
        -0.00006159359456140730,
        -0.00006877112565278292,
        0.00005961725726732511,
        0.00006665924082384822,
        -0.00005725954364258875,
        -0.00006407340935552097,
        0.00005448838302734356,
        0.00006096818645838748,
        -0.00005126935573384612,
        -0.00005729437913693051,
        0.00004756566594170946,
        0.00005299858640651649,
        -0.00004333802344478311,
        -0.00004802289326739944,
        0.00003854468714674325,
        0.00004230456495461973,
        -0.00003314164629036258,
        -0.00003577564276160680,
        0.00002708272959888446,
        0.00002836266080713883,
        -0.00002031973162184783,
        -0.00001998653437136059,
        0.00001280266527326317,
        0.00001056247323272506,
        -0.00000447997263493366,
        0.00000000000000018010,
        -0.00000470137542166504,
        -0.00001179680786950183,
        0.00001479581137585622,
        0.00002492894863656146,
        -0.00002585926034284999,
        -0.00003950199081521518,
        0.00003794952630246558,
        0.00005562533510390153,
        -0.00005112694449255346,
        -0.00007341140888130809,
        0.00006545547691674708,
        0.00009297493227531166,
        -0.00008100451468861596,
        -0.00011443219949984890,
        0.00009785125586799720,
        0.00013790069615213869,
        -0.00011608357081386009,
        -0.00016349957806345567,
        0.00013580361602766140,
        0.00019135095087333527,
        -0.00015713194703595793,
        -0.00022158186136626883,
        0.00018021143517098583,
        0.00025432756647353962,
        -0.00020521112493539825,
        -0.00028973617584148744,
        0.00023233050592626192,
        0.00032797403394144614,
        -0.00026180367902452943,
        -0.00036923242260961385,
        0.00029390302090533235,
        0.00041373732235860055,
        -0.00032894278845141303,
        -0.00046176281037360768,
        0.00036728127660995072,
        0.00051364800717821192,
        -0.00040931756980985552,
        -0.00056981819087065493,
        0.00045547980990656153,
        0.00063080833230949487,
        -0.00050620334909362726,
        -0.00069728246637329125,
        0.00056189657954768555,
        0.00077004110666809868,
        -0.00062289619331816687,
        -0.00085001115072575622,
        0.00068942348927680905,
        0.00093821589801631675,
        -0.00076155704372261131,
        -0.00103573239188887590,
        0.00083922780107206438,
        0.00114365637428966290,
        -0.00092222938331039438,
        -0.00126309285260670390,
        0.00101022856460441370,
        0.00139517639962364270,
        -0.00110274894053629850,
        -0.00154111562582135680,
        0.00119908301806405710,
        0.00170223363786462490,
        -0.00129808268855519670,
        -0.00187990070333909580,
        0.00139783679877188430,
        0.00207517252748098960,
        -0.00149544100855189110,
        -0.00228809924349417060,
        0.00158716226860971020,
        0.00251695944847457520,
        -0.00166911871878773860,
        -0.00275776668573988070,
        0.00173830522643889530,
        0.00300419409621456450,
        -0.00179374303516847230,
        -0.00324776304473811110,
        0.00183827444621076520,
        0.00347947070396771890,
        -0.00188005238476128150,
        -0.00369372646783595230,
        0.00193069845682608430,
        0.00389186350597909520,
        -0.00199927790643107370,
        -0.00408089170913615830,
        0.00208484779027301620,
        0.00426249950994375250,
        -0.00218104367632125650,
        -0.00442752406023235330,
        0.00228489927260688930,
        0.00456104950517442240,
        -0.00239163152757664900,
        -0.00463054828431928860,
        0.00250412111048623840,
        0.00457499561336300810,
        -0.00265315099925974390,
        -0.00427972751287817280,
        0.00300753205591187700,
        0.00371347946810307760,
        -0.00385349831880442110,
        -0.00311618850807916620,
        0.00527805820792147990,
        0.00274729809558833540,
        -0.00724490217494213030,
        -0.00288127752383099960,
        0.00945705430217480370,
        0.00335113576718646570,
        -0.01216716613200451900,
        -0.00454341282091311890,
        0.01552792173554723300,
        0.00808575033450806970,
        -0.01651715833904440800,
        -0.01125970042413330200,
        0.01556360660458855500,
        0.01245424603718856700,
        -0.01292946655706050900,
        -0.00700764376282207720,
        0.01699444868564858900,
        -0.00054889444565956098,
        -0.03631247649239682800,
        -0.01567018246199902000,
        0.03032681298582611000,
        0.00717077640302178540,
        -0.04647317941851894500,
        -0.00979674795909944890,
        0.06546125637052455100,
        0.00981001454035121050,
        -0.11112328224339996000,
        -0.01001341000213221800,
        0.33636842003978484000,
        0.53904770680793090000,
        0.33636842003978484000,
        -0.01001341000213221800,
        -0.11112328224339996000,
        0.00981001454035121050,
        0.06546125637052455100,
        -0.00979674795909944890,
        -0.04647317941851894500,
        0.00717077640302178540,
        0.03032681298582611000,
        -0.01567018246199902000,
        -0.03631247649239682800,
        -0.00054889444565956098,
        0.01699444868564858900,
        -0.00700764376282207720,
        -0.01292946655706050900,
        0.01245424603718856700,
        0.01556360660458855500,
        -0.01125970042413330200,
        -0.01651715833904440800,
        0.00808575033450806970,
        0.01552792173554723300,
        -0.00454341282091311890,
        -0.01216716613200451900,
        0.00335113576718646570,
        0.00945705430217480370,
        -0.00288127752383099960,
        -0.00724490217494213030,
        0.00274729809558833540,
        0.00527805820792147990,
        -0.00311618850807916620,
        -0.00385349831880442110,
        0.00371347946810307760,
        0.00300753205591187700,
        -0.00427972751287817280,
        -0.00265315099925974390,
        0.00457499561336300810,
        0.00250412111048623840,
        -0.00463054828431928860,
        -0.00239163152757664900,
        0.00456104950517442240,
        0.00228489927260688930,
        -0.00442752406023235330,
        -0.00218104367632125650,
        0.00426249950994375250,
        0.00208484779027301620,
        -0.00408089170913615830,
        -0.00199927790643107370,
        0.00389186350597909520,
        0.00193069845682608430,
        -0.00369372646783595230,
        -0.00188005238476128150,
        0.00347947070396771890,
        0.00183827444621076520,
        -0.00324776304473811110,
        -0.00179374303516847230,
        0.00300419409621456450,
        0.00173830522643889530,
        -0.00275776668573988070,
        -0.00166911871878773860,
        0.00251695944847457520,
        0.00158716226860971020,
        -0.00228809924349417060,
        -0.00149544100855189110,
        0.00207517252748098960,
        0.00139783679877188430,
        -0.00187990070333909580,
        -0.00129808268855519670,
        0.00170223363786462490,
        0.00119908301806405710,
        -0.00154111562582135680,
        -0.00110274894053629850,
        0.00139517639962364270,
        0.00101022856460441370,
        -0.00126309285260670390,
        -0.00092222938331039438,
        0.00114365637428966290,
        0.00083922780107206438,
        -0.00103573239188887590,
        -0.00076155704372261131,
        0.00093821589801631675,
        0.00068942348927680905,
        -0.00085001115072575622,
        -0.00062289619331816687,
        0.00077004110666809868,
        0.00056189657954768555,
        -0.00069728246637329125,
        -0.00050620334909362726,
        0.00063080833230949487,
        0.00045547980990656153,
        -0.00056981819087065493,
        -0.00040931756980985552,
        0.00051364800717821192,
        0.00036728127660995072,
        -0.00046176281037360768,
        -0.00032894278845141303,
        0.00041373732235860055,
        0.00029390302090533235,
        -0.00036923242260961385,
        -0.00026180367902452943,
        0.00032797403394144614,
        0.00023233050592626192,
        -0.00028973617584148744,
        -0.00020521112493539825,
        0.00025432756647353962,
        0.00018021143517098583,
        -0.00022158186136626883,
        -0.00015713194703595793,
        0.00019135095087333527,
        0.00013580361602766140,
        -0.00016349957806345567,
        -0.00011608357081386009,
        0.00013790069615213869,
        0.00009785125586799720,
        -0.00011443219949984890,
        -0.00008100451468861596,
        0.00009297493227531166,
        0.00006545547691674708,
        -0.00007341140888130809,
        -0.00005112694449255346,
        0.00005562533510390153,
        0.00003794952630246558,
        -0.00003950199081521518,
        -0.00002585926034284999,
        0.00002492894863656146,
        0.00001479581137585622,
        -0.00001179680786950183,
        -0.00000470137542166504,
        0.00000000000000018010,
        -0.00000447997263493366,
        0.00001056247323272506,
        0.00001280266527326317,
        -0.00001998653437136059,
        -0.00002031973162184783,
        0.00002836266080713883,
        0.00002708272959888446,
        -0.00003577564276160680,
        -0.00003314164629036258,
        0.00004230456495461973,
        0.00003854468714674325,
        -0.00004802289326739944,
        -0.00004333802344478311,
        0.00005299858640651649,
        0.00004756566594170946,
        -0.00005729437913693051,
        -0.00005126935573384612,
        0.00006096818645838748,
        0.00005448838302734356,
        -0.00006407340935552097,
        -0.00005725954364258875,
        0.00006665924082384822,
        0.00005961725726732511,
        -0.00006877112565278292,
        -0.00006159359456140730,
        0.00007045115232245183,
        0.00006321827266844918,
        -0.00007173825863247955,
        -0.00006451885308520020,
        0.00007266851482927465,
        0.00006552096644579134,
        -0.00007327550230351805,
        -0.00006624835394204421,
        0.00007359049584651454,
        0.00006672296548535658,
        -0.00007364253409666541,
        -0.00006696523428897633,
        0.00007345865882618404,
        0.00006699422409351832,
        -0.00007306414755741382,
        -0.00006682761805924579,
        0.00007248251890106898,
        0.00006648186394991408,
        -0.00007173557244691127,
        -0.00006597239912530587,
        0.00007084361039721578,
        0.00006531366047322778,
        -0.00006982553750434514,
        -0.00006451905237185399,
        0.00006869879735499293,
        0.00006360111441317727,
        -0.00006747946810776714,
        -0.00006257164222387489,
        0.00006618246148578504,
        0.00006144160351499846,
        -0.00006482152629021780,
        -0.00006022114712826031,
        0.00006340920810261755,
        0.00005891977109462683,
        -0.00006195701285256519,
        -0.00005754634036147779,
        0.00006047554891746109,
        0.00005610898842325228,
        -0.00005897447529284060,
        -0.00005461519652529477,
        0.00005746252757465475,
        0.00005307192896583540,
        -0.00005594770529247710,
        -0.00005148557821149205,
        0.00005443733115479129,
        0.00004986191276068639,
        -0.00005293798814064407,
        -0.00004820620748058719,
        0.00005145561039465569,
        0.00004652331722088406,
        -0.00004999563902841731,
        -0.00004481759258468633,
        0.00004856300467571614,
        0.00004309289614313631,
        -0.00004716209138430897,
        -0.00004135273921219533,
        0.00004579686342067475,
        0.00003960028723990231,
        -0.00004447095524544860,
        -0.00003783828739467259,
        0.00004318761060007382,
        0.00003606914062164350,
        -0.00004194969228433489,
        -0.00003429500440115735,
        0.00004075980768884570,
        0.00003251774843017896,
        -0.00003962032963259452,
        -0.00003073891990641706,
        0.00003853333195013365,
        0.00002895984119341026,
        -0.00003750064106009200,
        -0.00002718166024205022,
        0.00003652393131570097,
        0.00002540528775991868,
        -0.00003560469666339449,
        -0.00002363140558740922,
        0.00003474421002319449,
        0.00002186055955460343,
        -0.00003394359693044321,
        -0.00002009316301406014,
        0.00003320388882078312,
        0.00001832944259810734,
        -0.00003252597288626216,
        -0.00001656947867232582,
        0.00003191058266728210,
        0.00001481327533687927,
        -0.00003135837193615882,
        -0.00001306073523684171,
        0.00003086992995040929,
        0.00001131162710555502,
        -0.00003044573036866177,
        -0.00000956564174931897,
        0.00003008614585811939,
        0.00000782243590067508,
        -0.00002979150876567423,
        -0.00000608159587253740,
        0.00002956209972511065,
        0.00000434262703858279,
        -0.00002939810431896130,
        -0.00000260501350470779,
        0.00002929964100726002,
        0.00000086824106715644
    };

    static float x[Ntap];   //input samples
    float y = 0.0;            //output sample
    int n;

    //shift the old samples
    for (n = Ntap - 1; n > 0; n--)
        x[n] = x[n - 1];

    //Calculate the new output
    x[0] = (float)new_sample;
    for (n = 0; n < Ntap; n++)
        y += FIRCoef[n] * x[n];

    return (int)y;
}
