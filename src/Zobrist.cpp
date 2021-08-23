#include <string>
#include <map>
#include <stdlib.h>
#include <time.h>
#include "../include/const.h"
#include "../include/Zobrist.h"

using namespace std;

//为节省空间,将棋子与自然数一一对应
const int ctn2 = 2 * chess_type_num;

static map<char, int> chess2index;

static uint32_t zobrist_player_high32;									//高32位的黑方异或值
static uint32_t zobrist_random_list_high32[board_row][board_col][ctn2]; //高32位zobrist值,随机生成

static const uint32_t zobrist_player_low32 = 0x671e068a; //低32位的黑方异或值
//低32位的zobrist随机数组,按照RC4密码流生成,写成常量.
static const uint32_t zobrist_random_list_low32[board_row][board_col][ctn2] = {
	{
		{uint32_t(0xc12bd4bc), uint32_t(0x1c0c3b2d), uint32_t(0xbd30ba96), uint32_t(0xcea7117e), uint32_t(0x64960e62), uint32_t(0x1999595b), uint32_t(0x3105ea95), uint32_t(0xefa6b640), uint32_t(0x68daae23), uint32_t(0x4cd53b08), uint32_t(0xcd69ea80), uint32_t(0x36cb06c8), uint32_t(0x4b7fe672), uint32_t(0x32ea88df)},
		{uint32_t(0x52778821), uint32_t(0x52cd9a37), uint32_t(0x4239a747), uint32_t(0x4fbe0a61), uint32_t(0x15d540ea), uint32_t(0xdab336e3), uint32_t(0x5472f8b0), uint32_t(0x343b9de1), uint32_t(0x177dcee4), uint32_t(0xf21742ed), uint32_t(0xc58203af), uint32_t(0x2c9b4fb3), uint32_t(0xc017ee51), uint32_t(0xdbb03bcf)},
		{uint32_t(0x48462c68), uint32_t(0xecfd7fdb), uint32_t(0x6b6d4928), uint32_t(0xe617441d), uint32_t(0xdac39c3c), uint32_t(0xd517226f), uint32_t(0x564e4a5a), uint32_t(0x8fd47f24), uint32_t(0xdbb7172e), uint32_t(0xca0a8c6b), uint32_t(0x2bc43784), uint32_t(0xafac6ef3), uint32_t(0x7fc7d52c), uint32_t(0x1c0b4c33)},
		{uint32_t(0xd5d6fe07), uint32_t(0x3a602652), uint32_t(0x9c0632f8), uint32_t(0x5fa80b06), uint32_t(0x6950a3f1), uint32_t(0xbc4061b9), uint32_t(0xca81922a), uint32_t(0x9de1bedd), uint32_t(0xe38de802), uint32_t(0xb335515c), uint32_t(0x927a23ca), uint32_t(0xd042e54f), uint32_t(0x68603612), uint32_t(0xbbe1255)},
		{uint32_t(0xffa2bed5), uint32_t(0x10a0cb40), uint32_t(0x8ac36f4e), uint32_t(0x5a6a1232), uint32_t(0x261d14df), uint32_t(0xc5ff9f71), uint32_t(0x341993bf), uint32_t(0xffdf54af), uint32_t(0xf4bfa3aa), uint32_t(0x5434418b), uint32_t(0x3abcfa81), uint32_t(0x48fc82ea), uint32_t(0x5df4d8a3), uint32_t(0xc66a9af8)},
		{uint32_t(0xd372b581), uint32_t(0x1ae14aeb), uint32_t(0x6f99ac31), uint32_t(0x1de2f6f2), uint32_t(0x9dd524bf), uint32_t(0x573fd880), uint32_t(0xe81fe3f2), uint32_t(0x4965e9b6), uint32_t(0x99ce3e7b), uint32_t(0x5e07556d), uint32_t(0x805df3f0), uint32_t(0xff72871c), uint32_t(0xbb54ace3), uint32_t(0xa1e44fc9)},
		{uint32_t(0xc6a5079a), uint32_t(0xa0cbd2d0), uint32_t(0xc86773ef), uint32_t(0x6935f023), uint32_t(0x6de6133f), uint32_t(0x27de5d1d), uint32_t(0x6e75430a), uint32_t(0xcf43f632), uint32_t(0x645a2919), uint32_t(0x6455ec7), uint32_t(0x3ab1ff53), uint32_t(0x55975f9a), uint32_t(0xdfdde4d2), uint32_t(0x8d820f2b)},
		{uint32_t(0xc3fc131), uint32_t(0x339f82bf), uint32_t(0xc9c760ba), uint32_t(0x5291f849), uint32_t(0xb4e1dba1), uint32_t(0xae404994), uint32_t(0x4500b1a2), uint32_t(0x5e5b2ed3), uint32_t(0xb42ede09), uint32_t(0x85cdb52b), uint32_t(0xc69403c2), uint32_t(0x4b868add), uint32_t(0xff1d663d), uint32_t(0x29790f25)},
		{uint32_t(0x9f4b3237), uint32_t(0x64c993e6), uint32_t(0xe1a1afe8), uint32_t(0x9c6fb46b), uint32_t(0x40d73ddd), uint32_t(0x9017d1c8), uint32_t(0x29115069), uint32_t(0xb9327f5c), uint32_t(0xb332e243), uint32_t(0x3df5c354), uint32_t(0x94b3948d), uint32_t(0x17e3e691), uint32_t(0x82191bc4), uint32_t(0xd5ee11a2)},
	},
	{
		{uint32_t(0x197ab952), uint32_t(0x49c6201f), uint32_t(0xfe33e64b), uint32_t(0x34f5575f), uint32_t(0x4f2d6c99), uint32_t(0xaab18392), uint32_t(0x33bcd867), uint32_t(0x83ba0f9c), uint32_t(0x22c38c1e), uint32_t(0xc09e2223), uint32_t(0xc12c8f97), uint32_t(0x7b4ccc8d), uint32_t(0xbdf31b70), uint32_t(0x90808632)},
		{uint32_t(0x1af51b8), uint32_t(0x20114bf1), uint32_t(0x8b63fc8f), uint32_t(0xd0ef86fc), uint32_t(0xf2d8f5c3), uint32_t(0x9f17b8a4), uint32_t(0x4105c4cf), uint32_t(0x8c08de8f), uint32_t(0x699f0e33), uint32_t(0x6fcd8c50), uint32_t(0xc119adcd), uint32_t(0x12b0546b), uint32_t(0x3ed913be), uint32_t(0x4f6efdec)},
		{uint32_t(0x21b40318), uint32_t(0x48863584), uint32_t(0xe8982c1f), uint32_t(0x91bcce9e), uint32_t(0x77b35563), uint32_t(0x7a4a0607), uint32_t(0x828b980e), uint32_t(0xc0f396b7), uint32_t(0x3b8d8b9c), uint32_t(0xae2f02d2), uint32_t(0x1b3eb237), uint32_t(0x5e0a371f), uint32_t(0x706ab72a), uint32_t(0x5ed8bfe7)},
		{uint32_t(0xa76d9232), uint32_t(0x4cc9797), uint32_t(0x2c7a67ed), uint32_t(0xb1f8f95), uint32_t(0xf06e1be6), uint32_t(0xd720eebb), uint32_t(0xd13bf183), uint32_t(0x1d1e9dc6), uint32_t(0x1a5c1ddb), uint32_t(0xb4293269), uint32_t(0xd5f41f03), uint32_t(0x2a447b74), uint32_t(0xe1cfb398), uint32_t(0x8351211b)},
		{uint32_t(0x9063b3ec), uint32_t(0x884c9a14), uint32_t(0xbd7ef774), uint32_t(0xee5bf658), uint32_t(0x1c7d69a5), uint32_t(0xd00af69), uint32_t(0x3b06fbf4), uint32_t(0xab9e98b4), uint32_t(0x265d89f7), uint32_t(0xd6f5faab), uint32_t(0x832717e3), uint32_t(0x80a15398), uint32_t(0xed21ee73), uint32_t(0x3fce6012)},
		{uint32_t(0x40f41cf5), uint32_t(0x1072b84d), uint32_t(0xfca54a4a), uint32_t(0x7f4e51aa), uint32_t(0xfd59de1d), uint32_t(0xe39f063f), uint32_t(0xa8fd16d3), uint32_t(0xbd3b94ce), uint32_t(0x5aa52d25), uint32_t(0xd3c9218e), uint32_t(0x6196a601), uint32_t(0x11f524e8), uint32_t(0x4449af9e), uint32_t(0xac99a07d)},
		{uint32_t(0x56b1648), uint32_t(0xf70feb08), uint32_t(0x81e34a30), uint32_t(0xdef54d70), uint32_t(0x5fdf9b75), uint32_t(0x2af3313), uint32_t(0x5e9f5716), uint32_t(0x21fea239), uint32_t(0x935f2ed3), uint32_t(0x45404ad5), uint32_t(0xf18d9cc), uint32_t(0x69a0a57a), uint32_t(0xf1be9095), uint32_t(0x939e646d)},
		{uint32_t(0xb0e5651d), uint32_t(0x44197da1), uint32_t(0x53431ae7), uint32_t(0xd0ad2d80), uint32_t(0x708dd935), uint32_t(0xf19bca8f), uint32_t(0xc0f6c8fc), uint32_t(0xafc692bc), uint32_t(0x85775131), uint32_t(0x7f4ca4be), uint32_t(0xf980c79a), uint32_t(0x9f639356), uint32_t(0x2f012e27), uint32_t(0x55f7b3cb)},
		{uint32_t(0x9509f552), uint32_t(0x23cf85b4), uint32_t(0xf157515a), uint32_t(0x66e8db9), uint32_t(0xeec99614), uint32_t(0xe78d2753), uint32_t(0x3166878d), uint32_t(0x15e135f2), uint32_t(0xdfa67d32), uint32_t(0x55bbb8bc), uint32_t(0x5c06acfe), uint32_t(0x366fb6d6), uint32_t(0x23c7a4cb), uint32_t(0x25448cbe)},
	},
	{
		{uint32_t(0xd2023968), uint32_t(0xde28a2c1), uint32_t(0x81235092), uint32_t(0xae68e16d), uint32_t(0xef150a2a), uint32_t(0xe2b351f2), uint32_t(0xc39a440a), uint32_t(0xa929f776), uint32_t(0xbda81a9a), uint32_t(0xba2171fb), uint32_t(0xa9aaedc1), uint32_t(0x4c999790), uint32_t(0x61194760), uint32_t(0x53b98eaf)},
		{uint32_t(0x33c5661b), uint32_t(0xff9495fa), uint32_t(0x24675dd4), uint32_t(0x12441f0a), uint32_t(0xd8e57f1e), uint32_t(0x897d78cf), uint32_t(0xf01910b), uint32_t(0xbd3ea88e), uint32_t(0xc239619d), uint32_t(0x39dbd4ff), uint32_t(0xa72bc19c), uint32_t(0xcb41c13), uint32_t(0x9bf341ec), uint32_t(0x6bbe3a9a)},
		{uint32_t(0xf809454a), uint32_t(0x922e6570), uint32_t(0x38cc439f), uint32_t(0x45f731ec), uint32_t(0x2b6cabfe), uint32_t(0x5e3ef94b), uint32_t(0x30c370c9), uint32_t(0xa55fc062), uint32_t(0x412f4290), uint32_t(0x862ca60e), uint32_t(0x8114f02b), uint32_t(0xb55002f8), uint32_t(0x5d3e15d8), uint32_t(0x735b4a34)},
		{uint32_t(0xf3bc2b6a), uint32_t(0xeb55e55c), uint32_t(0xb4f10dda), uint32_t(0xcb4cb25f), uint32_t(0x54eb3300), uint32_t(0xe9f8794), uint32_t(0x52714e34), uint32_t(0xf6949d15), uint32_t(0x476202f1), uint32_t(0xb32d2440), uint32_t(0x2e8aec3b), uint32_t(0xba2da193), uint32_t(0xec5d8946), uint32_t(0x9e5834bd)},
		{uint32_t(0xd2776697), uint32_t(0xcb1b9de4), uint32_t(0xb751be3e), uint32_t(0xde531d52), uint32_t(0x3bc73281), uint32_t(0xb8d34cdf), uint32_t(0xd5182c3f), uint32_t(0xfcf2a73f), uint32_t(0xe82eaeaa), uint32_t(0x9b61c3e6), uint32_t(0xc2e49aeb), uint32_t(0x29e40210), uint32_t(0x89c9f158), uint32_t(0xe3544366)},
		{uint32_t(0xb5a41e86), uint32_t(0xa5f7953f), uint32_t(0x52b49dbc), uint32_t(0xfcf399f), uint32_t(0xdf77fa75), uint32_t(0x47cbca43), uint32_t(0xbea9815), uint32_t(0xcbc3161d), uint32_t(0xbd1c02d0), uint32_t(0xeea17d11), uint32_t(0x14470510), uint32_t(0xc9c0b1d5), uint32_t(0x22b719ae), uint32_t(0xa107db02)},
		{uint32_t(0x6d114bc3), uint32_t(0x9ab33983), uint32_t(0xda26c587), uint32_t(0x3fd7f48a), uint32_t(0x863dfc1c), uint32_t(0xd0809e8), uint32_t(0xe973aeb2), uint32_t(0xcfa7d2ce), uint32_t(0x5491dfef), uint32_t(0xf2b06bc1), uint32_t(0x5b09ce9a), uint32_t(0x6de93e7f), uint32_t(0x7a40f5bf), uint32_t(0x3d1e2379)},
		{uint32_t(0x64cdbe42), uint32_t(0x8c8d7b90), uint32_t(0x46c4119c), uint32_t(0x33efbbc1), uint32_t(0x5072c9a7), uint32_t(0x31bb41fd), uint32_t(0xd6c27318), uint32_t(0xee17d948), uint32_t(0x29459d93), uint32_t(0x7ddfa2aa), uint32_t(0x15a53e1d), uint32_t(0xd77cae9), uint32_t(0xbbca469d), uint32_t(0xb50a3d76)},
		{uint32_t(0xca7bb6d2), uint32_t(0xae305c07), uint32_t(0xd270a5e3), uint32_t(0x6da95e1a), uint32_t(0x76c9c9d2), uint32_t(0x5bedd7e5), uint32_t(0xe9f0b992), uint32_t(0xb4758bbb), uint32_t(0x6857e47f), uint32_t(0x7057a0bd), uint32_t(0x48bb2b0), uint32_t(0xfaee54ba), uint32_t(0x81d8534b), uint32_t(0x66ba727c)},
	},
	{
		{uint32_t(0xd5c8cd0), uint32_t(0x6ac95e57), uint32_t(0xbb2e75fd), uint32_t(0x7a4c53d8), uint32_t(0x221bb6b1), uint32_t(0xe8f3b876), uint32_t(0x94b1fa1), uint32_t(0x4433d6da), uint32_t(0x1e524c73), uint32_t(0xbb6ac0ab), uint32_t(0xc3ce6253), uint32_t(0xf51066b6), uint32_t(0x97d60193), uint32_t(0x4a00a649)},
		{uint32_t(0x212ed66f), uint32_t(0xe3714050), uint32_t(0xe2faf2fc), uint32_t(0xe415ff4e), uint32_t(0x399e666c), uint32_t(0x6809c00e), uint32_t(0x412cf2ae), uint32_t(0xe0042119), uint32_t(0xda3201e0), uint32_t(0x4f18427d), uint32_t(0x82a5e3dc), uint32_t(0xce8849fe), uint32_t(0xa938405), uint32_t(0xb6cd185c)},
		{uint32_t(0x6a87b0f1), uint32_t(0xeb5e9df2), uint32_t(0x2535c24d), uint32_t(0x29d6e6b4), uint32_t(0x31a847bc), uint32_t(0x7123f39), uint32_t(0x997a5f3a), uint32_t(0x5c966d1d), uint32_t(0x1122ac9a), uint32_t(0x1c283769), uint32_t(0xbb13c71d), uint32_t(0x15676e2f), uint32_t(0xaba76cfb), uint32_t(0x6f141214)},
		{uint32_t(0x2af34a58), uint32_t(0xd1a784c9), uint32_t(0x89c53cdb), uint32_t(0x485d8709), uint32_t(0x4620d96a), uint32_t(0x10760927), uint32_t(0xa57e41fd), uint32_t(0x1aa3a53f), uint32_t(0x1d72a816), uint32_t(0x61a230fb), uint32_t(0x405cc4c1), uint32_t(0xe69113ba), uint32_t(0x89ec86dd), uint32_t(0x2b6e2d49)},
		{uint32_t(0xf8ec01b1), uint32_t(0xaea295ac), uint32_t(0x163588e5), uint32_t(0x93d3103a), uint32_t(0x83e1babf), uint32_t(0xd97a3082), uint32_t(0xfdf10083), uint32_t(0xad80c41d), uint32_t(0x5c7fe64e), uint32_t(0xb188aac9), uint32_t(0x75ea867), uint32_t(0x78110b58), uint32_t(0xa6675ac3), uint32_t(0x2ec5da32)},
		{uint32_t(0x135f4d46), uint32_t(0x5c8457c5), uint32_t(0x820a4212), uint32_t(0xfce715a), uint32_t(0xb8e70144), uint32_t(0xdc12f049), uint32_t(0x992175cd), uint32_t(0x7138bde), uint32_t(0x5c0a326), uint32_t(0xba9b32d6), uint32_t(0x35cab917), uint32_t(0xb3ce9f75), uint32_t(0x2884785e), uint32_t(0xa31d2b98)},
		{uint32_t(0x36906f3f), uint32_t(0xe8d4894c), uint32_t(0x5a140ece), uint32_t(0x4d6efc7a), uint32_t(0x51e03d48), uint32_t(0xead7a05f), uint32_t(0x87072a4a), uint32_t(0x90470c78), uint32_t(0xebdbd607), uint32_t(0x707a79ed), uint32_t(0x740d92c7), uint32_t(0x219bab0e), uint32_t(0x39eb0e53), uint32_t(0x58a1d752)},
		{uint32_t(0x2d20303e), uint32_t(0xc4dd8d14), uint32_t(0x3876bdf6), uint32_t(0xf2a7f325), uint32_t(0x1afd4795), uint32_t(0x7703928f), uint32_t(0x237343b5), uint32_t(0xc978ad92), uint32_t(0xfb6837b0), uint32_t(0xc2988080), uint32_t(0x90e0e909), uint32_t(0x2292eaf0), uint32_t(0x7a46aae8), uint32_t(0xd51fc1c3)},
		{uint32_t(0x58169da0), uint32_t(0x7d13f919), uint32_t(0xee176290), uint32_t(0x6ac0b6bc), uint32_t(0x79e68975), uint32_t(0xc6b1dff3), uint32_t(0xb32490fb), uint32_t(0x81394d7e), uint32_t(0x5ba36caf), uint32_t(0x900a0c95), uint32_t(0x7a54c2a7), uint32_t(0x758e8dc7), uint32_t(0x7c9be904), uint32_t(0x505edf74)},
	},
	{
		{uint32_t(0xde0cf7b5), uint32_t(0x31c4bd4e), uint32_t(0xc3f7ae89), uint32_t(0xd7964499), uint32_t(0xb900f0cf), uint32_t(0x5a9ab57), uint32_t(0x6cf16824), uint32_t(0xa535d365), uint32_t(0xcc708511), uint32_t(0x48aff253), uint32_t(0xc97dbd7), uint32_t(0xd4cd1295), uint32_t(0x30f39719), uint32_t(0xd5ce2747)},
		{uint32_t(0x3a6d426d), uint32_t(0x387c4473), uint32_t(0x4bcec40), uint32_t(0x2c2f6de0), uint32_t(0xc1f5820), uint32_t(0x160e0bbf), uint32_t(0xffab445b), uint32_t(0xb07b0035), uint32_t(0x57f5ca2b), uint32_t(0x2477ea75), uint32_t(0xf1f92b8d), uint32_t(0x87eae89a), uint32_t(0x1cf32d9f), uint32_t(0x5f5da023)},
		{uint32_t(0x1677f4f), uint32_t(0x77743e82), uint32_t(0x4079f2bf), uint32_t(0x52c1b88e), uint32_t(0xeabe8c1e), uint32_t(0x82b5ccb8), uint32_t(0xa1136f6c), uint32_t(0xfe713f4f), uint32_t(0x318335a7), uint32_t(0x66539ff3), uint32_t(0xb5e3e7db), uint32_t(0x694ee00f), uint32_t(0x23c5ee60), uint32_t(0x8f649e44)},
		{uint32_t(0x830d7da5), uint32_t(0x326f2db7), uint32_t(0x43ffed40), uint32_t(0xc18d16dd), uint32_t(0x6fe9b82b), uint32_t(0xc77392d7), uint32_t(0x40688a2), uint32_t(0x3076b1ec), uint32_t(0x6e7dd21b), uint32_t(0x8ef31fbe), uint32_t(0x5412b9f7), uint32_t(0x3728e77), uint32_t(0x43fb4d2e), uint32_t(0x5cdffa5b)},
		{uint32_t(0xc206dc4d), uint32_t(0x164c4417), uint32_t(0xbb93306c), uint32_t(0x61c54db5), uint32_t(0x4956872a), uint32_t(0x19f71b1c), uint32_t(0x94f741c7), uint32_t(0x6736721e), uint32_t(0xdfcf5d62), uint32_t(0x14106a9f), uint32_t(0xc8e9bf2e), uint32_t(0xb6dd8dcc), uint32_t(0x648a3c83), uint32_t(0x2882878a)},
		{uint32_t(0xc63ded4d), uint32_t(0x4299feff), uint32_t(0x213e28bc), uint32_t(0xb19699dc), uint32_t(0xc194f7e), uint32_t(0xf0f0a3e8), uint32_t(0x5a39c7d0), uint32_t(0x8f7074e1), uint32_t(0x513bc929), uint32_t(0xc7b60d0b), uint32_t(0x9dd92ae4), uint32_t(0x62e84999), uint32_t(0x176bb04e), uint32_t(0x9beac4f0)},
		{uint32_t(0x1f30ae6a), uint32_t(0x7825dee3), uint32_t(0x651ed539), uint32_t(0x7932132e), uint32_t(0x54fc3e23), uint32_t(0x1b8c8e40), uint32_t(0xe943d96a), uint32_t(0x891b56db), uint32_t(0x1d3b04bc), uint32_t(0xb8a0cc14), uint32_t(0x2782e572), uint32_t(0xdd3673b9), uint32_t(0x575035d6), uint32_t(0xae3aae91)},
		{uint32_t(0xb8fcfbaf), uint32_t(0xa8ae4d3f), uint32_t(0x14d6f88f), uint32_t(0x9453e7bf), uint32_t(0xe04751f5), uint32_t(0xf285a05), uint32_t(0xfcff76ec), uint32_t(0xccc18639), uint32_t(0x1a6012a4), uint32_t(0xcb7a218), uint32_t(0x2c1b7741), uint32_t(0x90fec619), uint32_t(0x97d59cce), uint32_t(0xbaebbf6d)},
		{uint32_t(0xd9e0784d), uint32_t(0xb269d223), uint32_t(0xc1d8f0d9), uint32_t(0x5d58c306), uint32_t(0x7cd6d094), uint32_t(0x87d74262), uint32_t(0x99f4bc77), uint32_t(0xe26f211b), uint32_t(0xac7554c5), uint32_t(0xe623402a), uint32_t(0x28d28a8a), uint32_t(0x1b43f9c9), uint32_t(0x932ecb07), uint32_t(0xe50af35a)},
	},
	{
		{uint32_t(0xcaa85ac3), uint32_t(0xcd22ac4c), uint32_t(0xbf5dba63), uint32_t(0xca32f606), uint32_t(0x93314b8), uint32_t(0xd9e2d040), uint32_t(0x460ab67c), uint32_t(0x373b789c), uint32_t(0x820f817d), uint32_t(0xe7ccdff1), uint32_t(0xb7dcb0aa), uint32_t(0xfab6a635), uint32_t(0x318396bb), uint32_t(0xf8890af6)},
		{uint32_t(0x5a86fd9a), uint32_t(0xd3e08d4), uint32_t(0xb5bb148d), uint32_t(0xf75e7e52), uint32_t(0x738e4fb8), uint32_t(0xc16e9994), uint32_t(0x93e52c1f), uint32_t(0x3148da45), uint32_t(0x7c2cc09f), uint32_t(0xf8374873), uint32_t(0x822571b8), uint32_t(0xa6aff83e), uint32_t(0xf45038a), uint32_t(0x9a207ea2)},
		{uint32_t(0xd9461a92), uint32_t(0x1562be38), uint32_t(0xbcfc9f6c), uint32_t(0x542bc873), uint32_t(0x6c00c665), uint32_t(0x5d08364e), uint32_t(0xc29679f5), uint32_t(0xb8d931c5), uint32_t(0x6c620d0b), uint32_t(0xe4feae63), uint32_t(0xf474c1cd), uint32_t(0xa0d97ba3), uint32_t(0xd999160d), uint32_t(0x2982f0fc)},
		{uint32_t(0xa293f06), uint32_t(0xd57b40a4), uint32_t(0xff61f046), uint32_t(0x54df6852), uint32_t(0xaa8b673a), uint32_t(0xf1c70c72), uint32_t(0xdcbf977f), uint32_t(0xded38872), uint32_t(0x82b137d3), uint32_t(0xe4ce4596), uint32_t(0xa48795c8), uint32_t(0xd425c087), uint32_t(0x9d59ac71), uint32_t(0x120d6546)},
		{uint32_t(0x6ddafd07), uint32_t(0xa64ab638), uint32_t(0x1ea0561c), uint32_t(0x2538f308), uint32_t(0x888d5b09), uint32_t(0xeb6ec643), uint32_t(0x8033405a), uint32_t(0xea44a0d2), uint32_t(0xa6f5d54c), uint32_t(0xb561df43), uint32_t(0x4084d1ef), uint32_t(0x53ee51d5), uint32_t(0x51408a0b), uint32_t(0x837e1298)},
		{uint32_t(0x7db5f1d3), uint32_t(0x802abc56), uint32_t(0xbc931f55), uint32_t(0xad6c412), uint32_t(0xb4d80c71), uint32_t(0xc519c24), uint32_t(0xa874f5a4), uint32_t(0xc879e41c), uint32_t(0x8480f043), uint32_t(0x9faef806), uint32_t(0x907351c3), uint32_t(0x592852a), uint32_t(0x2b6bc685), uint32_t(0xead6b8d1)},
		{uint32_t(0xd48fcbc7), uint32_t(0xb98e7f6e), uint32_t(0x68e860bb), uint32_t(0xeb4d9c9a), uint32_t(0xaf67cbe1), uint32_t(0x86c5f657), uint32_t(0x1ba5fe79), uint32_t(0xeae56162), uint32_t(0x65c94d75), uint32_t(0xb60dd6a8), uint32_t(0x10bb6966), uint32_t(0x37d62a3a), uint32_t(0xd1914549), uint32_t(0x1e6c2023)},
		{uint32_t(0x588392f9), uint32_t(0x25cf18e1), uint32_t(0xebf0cc99), uint32_t(0x93b5e86), uint32_t(0xa4cc1ec2), uint32_t(0x883100b2), uint32_t(0x6dad8e43), uint32_t(0xfe379857), uint32_t(0x53e1037d), uint32_t(0x272a5996), uint32_t(0x18ac1b79), uint32_t(0x3ea9e9e5), uint32_t(0xa8f2a87e), uint32_t(0x950e94b6)},
		{uint32_t(0x50ea5766), uint32_t(0xe3b7251a), uint32_t(0xa95685e0), uint32_t(0x6930412c), uint32_t(0xb661611b), uint32_t(0x62bfc838), uint32_t(0x886f08dd), uint32_t(0xe6155602), uint32_t(0x6a11b2c3), uint32_t(0x63ba6c24), uint32_t(0x13dac74d), uint32_t(0xfc58d2), uint32_t(0x75b295c4), uint32_t(0x75fa728c)},
	},
	{
		{uint32_t(0x25f4c749), uint32_t(0x4a0276cf), uint32_t(0x340e46de), uint32_t(0xaa4ba792), uint32_t(0x1832bade), uint32_t(0x515967c), uint32_t(0x261f26e9), uint32_t(0xa7f863c6), uint32_t(0xc5ddab6e), uint32_t(0xea5110ce), uint32_t(0x4ff54f6f), uint32_t(0xfea79d84), uint32_t(0xd7deee45), uint32_t(0xf8ebadf1)},
		{uint32_t(0x5d93ba99), uint32_t(0xca257934), uint32_t(0xf0095fe2), uint32_t(0x29388f29), uint32_t(0x3a5dd7a2), uint32_t(0x4f64c905), uint32_t(0xf90f6767), uint32_t(0x888b4316), uint32_t(0x45d998cd), uint32_t(0xec937ae), uint32_t(0xf28e8a83), uint32_t(0x61296844), uint32_t(0x79a75cc3), uint32_t(0x33df86cf)},
		{uint32_t(0xd86a8e12), uint32_t(0xee8d6c52), uint32_t(0x9b50267b), uint32_t(0x7d39723f), uint32_t(0x40f27f8b), uint32_t(0x108cf12c), uint32_t(0x774a7ade), uint32_t(0xcf976955), uint32_t(0x4c6ea2d3), uint32_t(0x8ced2bb8), uint32_t(0xa4dc515a), uint32_t(0x9cb19f0a), uint32_t(0x2a530b69), uint32_t(0xd8b0b5c5)},
		{uint32_t(0x48b33565), uint32_t(0xeab659e6), uint32_t(0x6bfadfe6), uint32_t(0x47a6d51b), uint32_t(0xe58f4049), uint32_t(0x561e71dd), uint32_t(0x4349431d), uint32_t(0x9fa44a4b), uint32_t(0x37b1edef), uint32_t(0x39dc37d9), uint32_t(0x6e7180ef), uint32_t(0x7858da94), uint32_t(0x1a613d05), uint32_t(0xde6b62b1)},
		{uint32_t(0xf2a55e29), uint32_t(0x1713b6fa), uint32_t(0xf384eea0), uint32_t(0xa0f04ea), uint32_t(0x1940ce49), uint32_t(0xd7b8f04d), uint32_t(0x60ddd3d), uint32_t(0x18403abb), uint32_t(0x79fa7161), uint32_t(0x15fb13ab), uint32_t(0x65c00533), uint32_t(0x76e94776), uint32_t(0xa771c8c9), uint32_t(0xa970dbda)},
		{uint32_t(0x1301aea7), uint32_t(0x506ab178), uint32_t(0xc7ee49a9), uint32_t(0xe7e6ce3e), uint32_t(0xe1bb9e32), uint32_t(0x55b7d5ab), uint32_t(0x45c94ee5), uint32_t(0x8a237e9f), uint32_t(0x1453e741), uint32_t(0x4f3000fb), uint32_t(0xf9c65d94), uint32_t(0x2dfaa969), uint32_t(0xe7596c69), uint32_t(0x739433e)},
		{uint32_t(0x40c4d4da), uint32_t(0xb8094da8), uint32_t(0x9927d97c), uint32_t(0x6a6607d3), uint32_t(0xcb6c34c8), uint32_t(0xdcdd728a), uint32_t(0x315df25), uint32_t(0xa10e4cc3), uint32_t(0x54dc112b), uint32_t(0x54949c8), uint32_t(0xdc45d3fd), uint32_t(0x898e256e), uint32_t(0x67866468), uint32_t(0x17851f31)},
		{uint32_t(0xb70f6737), uint32_t(0x703f6893), uint32_t(0xbf0bd2c0), uint32_t(0xf585dee8), uint32_t(0xa0cef8b0), uint32_t(0xd119bbb), uint32_t(0xaaeaebdc), uint32_t(0xb3e74b83), uint32_t(0x58c1efd7), uint32_t(0x15d3f4b5), uint32_t(0x38791e93), uint32_t(0xc0024592), uint32_t(0xc07d3d7d), uint32_t(0xea67be75)},
		{uint32_t(0x66d9625d), uint32_t(0xa020d26e), uint32_t(0xfb538d4b), uint32_t(0x72cea246), uint32_t(0x4472584f), uint32_t(0x49d8b630), uint32_t(0x7c784464), uint32_t(0x15a37345), uint32_t(0xd71e9914), uint32_t(0xad44a21f), uint32_t(0x56961542), uint32_t(0x42b7e346), uint32_t(0x51d3e12b), uint32_t(0x468b5695)},
	},
	{
		{uint32_t(0xf389de97), uint32_t(0x568ca43), uint32_t(0xb682ad89), uint32_t(0x312c39f1), uint32_t(0x8eb30ee1), uint32_t(0x960cc2a6), uint32_t(0xb2a6d7c3), uint32_t(0xa6866fd8), uint32_t(0x4943cd2d), uint32_t(0x11d450d8), uint32_t(0x2d867367), uint32_t(0x609678df), uint32_t(0xbccbc889), uint32_t(0x530901f7)},
		{uint32_t(0x538925ed), uint32_t(0x8563f7ff), uint32_t(0x3891636a), uint32_t(0xbc8ca846), uint32_t(0xe4a53680), uint32_t(0x9077a053), uint32_t(0x29ba0295), uint32_t(0xeac544ef), uint32_t(0xc8f9bb3f), uint32_t(0xdf28fada), uint32_t(0x5df59d0), uint32_t(0xae188eb1), uint32_t(0xfa782cdb), uint32_t(0xb414ab84)},
		{uint32_t(0x182b72dc), uint32_t(0x49ce085a), uint32_t(0x6c65e73b), uint32_t(0x9442bee3), uint32_t(0xd7bcfcb0), uint32_t(0xbf5e0f94), uint32_t(0x8ac9bdb4), uint32_t(0x2b538fd3), uint32_t(0x60f81a79), uint32_t(0x690a7aaf), uint32_t(0xf7059ff2), uint32_t(0xe2898a14), uint32_t(0x2220a35a), uint32_t(0x24797ee7)},
		{uint32_t(0x7df635e8), uint32_t(0x7636d2ad), uint32_t(0x67364291), uint32_t(0xa6dab949), uint32_t(0x3b1874c2), uint32_t(0x984c5593), uint32_t(0x810c653b), uint32_t(0x61dc7abb), uint32_t(0xae2e8033), uint32_t(0xa7a49520), uint32_t(0x2e09a96), uint32_t(0xfda93451), uint32_t(0xf1f77bb3), uint32_t(0x99adc6b7)},
		{uint32_t(0xa0491978), uint32_t(0x81e885db), uint32_t(0x1def2ae9), uint32_t(0x4b0fede), uint32_t(0xae8b05c6), uint32_t(0x6899456e), uint32_t(0x7715652c), uint32_t(0xfd6241f3), uint32_t(0x56f91b79), uint32_t(0x93c03e24), uint32_t(0x94d2ccd6), uint32_t(0xbc8aab00), uint32_t(0xc879f966), uint32_t(0xc6a6b1d8)},
		{uint32_t(0x98522500), uint32_t(0x838bc448), uint32_t(0x8787df94), uint32_t(0x94f3a48b), uint32_t(0x38d3c477), uint32_t(0x7c7fd0d3), uint32_t(0x43129005), uint32_t(0x788d3386), uint32_t(0xdd6af6ad), uint32_t(0xba1a1e70), uint32_t(0x5202528), uint32_t(0xbf3fea00), uint32_t(0x3abd6d14), uint32_t(0xcf7a2329)},
		{uint32_t(0xa459d329), uint32_t(0x92090e35), uint32_t(0xb6280ab5), uint32_t(0x1134209e), uint32_t(0x15d9ba00), uint32_t(0xd2653410), uint32_t(0x8d18f79f), uint32_t(0x3bbacd6a), uint32_t(0x25155f00), uint32_t(0x27413b2f), uint32_t(0xb7467c95), uint32_t(0xb7195d77), uint32_t(0x10fd998d), uint32_t(0x1514d572)},
		{uint32_t(0x3018a945), uint32_t(0xde0cc6fd), uint32_t(0x64e21329), uint32_t(0xe1fd6322), uint32_t(0x2e32ca8e), uint32_t(0x9eaab3a3), uint32_t(0xe2a33ca2), uint32_t(0x5dbf0500), uint32_t(0x66a7d5fc), uint32_t(0x8b5071d9), uint32_t(0xdc7ea89e), uint32_t(0x4ee66833), uint32_t(0x9318a836), uint32_t(0x6bec531c)},
		{uint32_t(0xbe2d2686), uint32_t(0x19c59ad2), uint32_t(0x59b32115), uint32_t(0x8f90e212), uint32_t(0x1ef9c777), uint32_t(0x4d3cdb8a), uint32_t(0x33af2372), uint32_t(0x8f4ced79), uint32_t(0xd098fda2), uint32_t(0xb0e2c97a), uint32_t(0x25a5fd29), uint32_t(0x75f165c0), uint32_t(0xe2842e62), uint32_t(0xcd793e9c)},
	},
	{
		{uint32_t(0xe6427d70), uint32_t(0xd9a06e74), uint32_t(0xa91aee7d), uint32_t(0xeffe4fac), uint32_t(0xd402a948), uint32_t(0xfde5fce), uint32_t(0x95be6a16), uint32_t(0xf5c1a865), uint32_t(0xb8534460), uint32_t(0xeaa55a18), uint32_t(0x57bc6161), uint32_t(0x717eca46), uint32_t(0xfd71e01a), uint32_t(0x613a4821)},
		{uint32_t(0x9c6348a5), uint32_t(0x8ed71eae), uint32_t(0x914e097b), uint32_t(0x2ba9ec9b), uint32_t(0x61ab8935), uint32_t(0x8b784064), uint32_t(0x1757b71), uint32_t(0x94a0c677), uint32_t(0xb67ff27f), uint32_t(0x8e83b3a0), uint32_t(0x7731bb79), uint32_t(0x43de8efa), uint32_t(0x5cc7854b), uint32_t(0x57362e53)},
		{uint32_t(0xc68babdc), uint32_t(0x4760cf07), uint32_t(0x9bcdeca1), uint32_t(0x390b8dde), uint32_t(0x52942db), uint32_t(0x6a78cb7c), uint32_t(0xd3d237e3), uint32_t(0x4fc46b5d), uint32_t(0x8293e48a), uint32_t(0xe3dc7b00), uint32_t(0x26836125), uint32_t(0x21679ff7), uint32_t(0xdfaaae1e), uint32_t(0xeec2bd81)},
		{uint32_t(0x703bdd20), uint32_t(0xd66ecf33), uint32_t(0xca776d90), uint32_t(0x9c6753d0), uint32_t(0x92b2cdcd), uint32_t(0x68372f6f), uint32_t(0xbd3f6311), uint32_t(0x29da75ff), uint32_t(0x90cf496f), uint32_t(0x312b8e11), uint32_t(0xc4b55c99), uint32_t(0xdc5c790), uint32_t(0x1d6373cf), uint32_t(0x5d4567ee)},
		{uint32_t(0x7eb895bf), uint32_t(0x3b35939b), uint32_t(0x692a6ec8), uint32_t(0xcba78428), uint32_t(0xef4c6234), uint32_t(0x89cd377e), uint32_t(0x8ac47c95), uint32_t(0xaedfcc71), uint32_t(0x3f93c3b4), uint32_t(0x78cd6a8b), uint32_t(0x818be869), uint32_t(0x18e85347), uint32_t(0x20909762), uint32_t(0xc95f8ab9)},
		{uint32_t(0xad39f3c3), uint32_t(0x9f26fba5), uint32_t(0x87f2ddbd), uint32_t(0xae6d03ea), uint32_t(0xf5576c27), uint32_t(0xf506ab79), uint32_t(0xefb95a71), uint32_t(0x233bf8be), uint32_t(0xc822a24d), uint32_t(0xd9579b0c), uint32_t(0x156a6135), uint32_t(0x5605c121), uint32_t(0x4233dada), uint32_t(0x22ecbe0a)},
		{uint32_t(0xb83cd51a), uint32_t(0xb5072224), uint32_t(0xeb257b6a), uint32_t(0xbea02670), uint32_t(0x3135e9d0), uint32_t(0xfcdc9af7), uint32_t(0x732a0bc9), uint32_t(0x5a979476), uint32_t(0x30bafc27), uint32_t(0x407450c5), uint32_t(0xc2f5dcc3), uint32_t(0xf0fce21), uint32_t(0x797b7cac), uint32_t(0x299dbfb)},
		{uint32_t(0xdaaeca4b), uint32_t(0x62083bc7), uint32_t(0x43fb8536), uint32_t(0xf7e236f3), uint32_t(0x8007ddca), uint32_t(0xc74d308e), uint32_t(0x9721cf4), uint32_t(0xa5b093a5), uint32_t(0x249d3ec3), uint32_t(0x523c512a), uint32_t(0xa090b4e3), uint32_t(0xe45c33d8), uint32_t(0x847f913), uint32_t(0x3199daed)},
		{uint32_t(0x38957860), uint32_t(0x51226620), uint32_t(0xcacddab9), uint32_t(0x3a0fde04), uint32_t(0x124521d3), uint32_t(0xe26c7d42), uint32_t(0xadadc54b), uint32_t(0xe0fba329), uint32_t(0x960d13bf), uint32_t(0x2c96153c), uint32_t(0x5dd3d819), uint32_t(0x4c1ee3f9), uint32_t(0x63a78c33), uint32_t(0x8b7041a1)},
	},
	{
		{uint32_t(0x78987e64), uint32_t(0xab1d8a49), uint32_t(0xde722f13), uint32_t(0x19c145b0), uint32_t(0xbac5c4e9), uint32_t(0xd4b3acc8), uint32_t(0x2f28c840), uint32_t(0x85670983), uint32_t(0x24180ffc), uint32_t(0x9c2d928e), uint32_t(0x48776b24), uint32_t(0xf6dca56d), uint32_t(0xdd25d4ab), uint32_t(0x2f7959a3)},
		{uint32_t(0x27a07441), uint32_t(0x2ded41c), uint32_t(0x5ea4ecb0), uint32_t(0xbc7f8a93), uint32_t(0xffe955b2), uint32_t(0xa70992d6), uint32_t(0xcc18525f), uint32_t(0x1576cf0e), uint32_t(0xe31e876b), uint32_t(0x9a1f1f2a), uint32_t(0x324af16d), uint32_t(0xba5e57e1), uint32_t(0xb07d4e5b), uint32_t(0x10f58ca0)},
		{uint32_t(0x951cccde), uint32_t(0x18378d56), uint32_t(0x8503f055), uint32_t(0x35145584), uint32_t(0x43dde18b), uint32_t(0x3d145b9a), uint32_t(0xa77089d9), uint32_t(0x2344324b), uint32_t(0x6fa90637), uint32_t(0xf378cba7), uint32_t(0xefc50dc4), uint32_t(0x156e24cd), uint32_t(0x3d1e5b73), uint32_t(0xcd0b2318)},
		{uint32_t(0x26920959), uint32_t(0xf3d90faa), uint32_t(0xfd2dec7a), uint32_t(0x547e06a8), uint32_t(0xfb4eb975), uint32_t(0x79e21142), uint32_t(0xdb176609), uint32_t(0xd2b83b26), uint32_t(0xdafcacec), uint32_t(0x9c3d43b4), uint32_t(0xd472750b), uint32_t(0x728700da), uint32_t(0x7994b5a7), uint32_t(0x7ab8461e)},
		{uint32_t(0x1e3a16eb), uint32_t(0x8c6dfca2), uint32_t(0x8a7ea731), uint32_t(0x1133f2c4), uint32_t(0x2c7052c4), uint32_t(0xe963e842), uint32_t(0x9d1edbfb), uint32_t(0xd1effb75), uint32_t(0x94d49fc7), uint32_t(0xf68cf18a), uint32_t(0xae9774c3), uint32_t(0x7fc9ca5b), uint32_t(0x2bd1b539), uint32_t(0x25fc6357)},
		{uint32_t(0x3304854), uint32_t(0xcbf3e41f), uint32_t(0x3ced5bbb), uint32_t(0xda3c4e19), uint32_t(0xdfaa767b), uint32_t(0xdfac5db9), uint32_t(0x5ef0d77a), uint32_t(0xb53503d1), uint32_t(0x269cfdc7), uint32_t(0xebbaf0fb), uint32_t(0xb6b457ca), uint32_t(0x1af8f9a8), uint32_t(0x19c3f1eb), uint32_t(0xfc0cf28a)},
		{uint32_t(0x857e9f29), uint32_t(0xd427f789), uint32_t(0x95252944), uint32_t(0x1f3ba93d), uint32_t(0xe562b36d), uint32_t(0x757192fc), uint32_t(0xe6a39e04), uint32_t(0xc5324f39), uint32_t(0xac896bfe), uint32_t(0xe5f87285), uint32_t(0xd5977446), uint32_t(0x1dbb153a), uint32_t(0x26e9f601), uint32_t(0xd73d1e0c)},
		{uint32_t(0xd5fcc55c), uint32_t(0x41ed0a2b), uint32_t(0xf0ede89), uint32_t(0x2e48c025), uint32_t(0x5412d4af), uint32_t(0x31a9f6b3), uint32_t(0x2f234ecd), uint32_t(0x96f295f), uint32_t(0xaea2b985), uint32_t(0x123c188f), uint32_t(0xe432f46f), uint32_t(0xa53d7513), uint32_t(0xba045feb), uint32_t(0x5f8e5999)},
		{uint32_t(0xd981ed71), uint32_t(0xba86e53c), uint32_t(0xad9ff567), uint32_t(0xf7d9bc55), uint32_t(0xba136861), uint32_t(0x824dca4e), uint32_t(0xf1837988), uint32_t(0x12d7d5f2), uint32_t(0x536c4d64), uint32_t(0xdb8922c5), uint32_t(0x4983edec), uint32_t(0xbaa01c6), uint32_t(0x4b55b6b9), uint32_t(0x459d003b)},
	},
};

static const U64 rand64(void)
{ //产生64位随机数
	return rand() ^ ((U64)rand() << 15) ^ ((U64)rand() << 30) ^ ((U64)rand() << 45) ^ ((U64)rand() << 60);
}

static const U32 rand32(void)
{
	return rand() ^ ((U32)rand() << 15) ^ ((U32)rand() << 30);
}

static string get_mirror_move(const string &move)
{
	int from_c, to_c;
	string mirr_move = move;

	from_c = board_col - move[1] - 1 + '0' + '0';
	to_c = board_col - move[3] - 1 + '0' + '0';

	mirr_move[1] = from_c;
	mirr_move[3] = to_c;

	return mirr_move;
}
/*********************************************************
* 函数名: init_zobrist
* 功能:  初始化zobrist中使用到的各项随机数和map等数据
*********************************************************/
void init_zobrist()
{
	/*fen规则
	r车 n马 b相 a士 k帅 c炮 p兵
	按照fen规则b是黑r是红
	*/
	srand((unsigned int)(time(NULL)));
	//srand(unsigned int(1));
	U64 result = 0; //初始局面的zobrist值

	chess2index['K'] = 0;
	chess2index['A'] = 1;
	chess2index['B'] = 2;
	chess2index['N'] = 3;
	chess2index['R'] = 4;
	chess2index['C'] = 5;
	chess2index['P'] = 6;
	chess2index['k'] = chess2index['K'] + chess_type_num;
	chess2index['a'] = chess2index['A'] + chess_type_num;
	chess2index['b'] = chess2index['B'] + chess_type_num;
	chess2index['n'] = chess2index['N'] + chess_type_num;
	chess2index['r'] = chess2index['R'] + chess_type_num;
	chess2index['c'] = chess2index['C'] + chess_type_num;
	chess2index['p'] = chess2index['P'] + chess_type_num;

	for (int i = 0; i < board_row; i++)
		for (int j = 0; j < board_col; j++)
			for (int k = 0; k < ctn2; k++)
				zobrist_random_list_high32[i][j][k] = rand32();

	zobrist_player_high32 = rand32();
}
/*********************************************************
* 函数名: get_zobrist_by_board
* 功能:  根据棋盘和当前下棋的人生成zobrist值
* board: 当前棋盘
* player: 当前走棋方
* 返回值: 棋盘的zobrist值
*********************************************************/
U64 get_zobrist_by_board(const char (&board)[board_row][board_col], const char player)
{
	U64 result = 0; //初始局面的zobrist值

	for (int i = 0; i < board_row; i++)
		for (int j = 0; j < board_col; j++)
			if (board[i][j] != '\0')
			{
				int chesstype = chess2index[board[i][j]];
				result ^= ((uint64_t)zobrist_random_list_high32[i][j][chesstype] << 32);
				result ^= (uint64_t)zobrist_random_list_low32[i][j][chesstype];
			}

	if (player == 'b')
	{
		result ^= ((uint64_t)zobrist_player_high32 << 32);
		result ^= (uint64_t)zobrist_player_low32;
	}

	return result;
}
/*********************************************************
* 函数名: get_mirror_zobrist_by_board
* 功能:  根据棋盘和当前下棋的人生成**镜像局面**zobrist值
* board: 当前棋盘
* player: 当前走棋方
* 返回值: **镜像局面**棋盘的zobrist值
*********************************************************/
U64 get_mirror_zobrist_by_board(const char (&board)[board_row][board_col], const char player)
{
	U64 result = 0; //初始局面的zobrist值

	for (int i = 0; i < board_row; i++)
		for (int j = 0; j < board_col; j++)
			if (board[i][j] != '\0')
			{
				int chesstype = chess2index[board[i][j]];
				int mirr_i = i; //镜像时,行不变
				int mirr_j = board_col - j - 1;
				result ^= ((uint64_t)zobrist_random_list_high32[mirr_i][mirr_j][chesstype] << 32);
				result ^= (uint64_t)zobrist_random_list_low32[mirr_i][mirr_j][chesstype];
			}

	if (player == 'b')
	{
		result ^= ((uint64_t)zobrist_player_high32 << 32);
		result ^= (uint64_t)zobrist_player_low32;
	}

	return result;
}
/*********************************************************
* 函数名: get_zobrist_by_move
* 功能:  根据原zobrist值,棋盘和走法,计算走一步后的zobrist值
* board: 当前棋盘
* zobrist_old: 走之前的zobrist值
* move: 着法. 如1234,表示1行2列走到3行4列
* 返回值: 按照move走了一步以后的新棋盘的zobrist值
*********************************************************/
U64 get_zobrist_by_move(const char (&board)[board_row][board_col], const U64 zobrist_old, const string &move)
{
	U64 zobrist_value_new = zobrist_old;
	int from_r, from_c, to_r, to_c;

	from_r = move[0] - '0';
	from_c = move[1] - '0';
	to_r = move[2] - '0';
	to_c = move[3] - '0';

	//清除目标位置的值
	if (board[to_r][to_c] != '\0')
	{
		char chesstype = chess2index[board[to_r][to_c]];
		zobrist_value_new ^= ((uint64_t)zobrist_random_list_high32[to_r][to_c][chesstype] << 32);
		zobrist_value_new ^= (uint64_t)zobrist_random_list_low32[to_r][to_c][chesstype];
	}
	//清除原位置值
	char chesstype = chess2index[board[from_r][from_c]];
	zobrist_value_new ^= ((uint64_t)zobrist_random_list_high32[from_r][from_c][chesstype] << 32);
	zobrist_value_new ^= (uint64_t)zobrist_random_list_low32[from_r][from_c][chesstype];
	//更新目标位置值
	zobrist_value_new ^= ((uint64_t)zobrist_random_list_high32[to_r][to_c][chesstype] << 32);
	zobrist_value_new ^= (uint64_t)zobrist_random_list_low32[to_r][to_c][chesstype];

	//走完一步后,player交换
	zobrist_value_new ^= ((uint64_t)zobrist_player_high32 << 32);
	zobrist_value_new ^= (uint64_t)zobrist_player_low32;

	return zobrist_value_new;
}
/*********************************************************
* 函数名: get_mirror_zobrist_by_move
* 功能:  根据原**镜像局面**zobrist值,棋盘和走法,计算走一步后的**镜像局面**zobrist值
* board: 当前棋盘
* mirr_zobrist_old: 走之前**镜像局面**的zobrist值
* move: 着法. 如1234,表示1行2列走到3行4列
* 返回值: 按照move走了一步以后的**镜像局面**新棋盘的zobrist值
* 注意: board和move均传入正向即可,函数中会自动转换.
*********************************************************/
U64 get_mirror_zobrist_by_move(const char (&board)[board_row][board_col], const U64 mirr_zobrist_old, const string &move)
{
	U64 zobrist_value_new = mirr_zobrist_old;
	string mirr_move;
	int chesstype, chesstype_old_to;
	int from_r, from_c, to_r, to_c;

	from_r = move[0] - '0';
	from_c = move[1] - '0';
	to_r = move[2] - '0';
	to_c = move[3] - '0';
	chesstype = chess2index[board[from_r][from_c]];
	chesstype_old_to = board[to_r][to_c] == '\0' ? -1 : chess2index[board[to_r][to_c]];

	mirr_move = get_mirror_move(move);
	from_r = mirr_move[0] - '0';
	from_c = mirr_move[1] - '0';
	to_r = mirr_move[2] - '0';
	to_c = mirr_move[3] - '0';

	//清除目标位置的值
	if (chesstype_old_to >= 0)
	{
		zobrist_value_new ^= ((uint64_t)zobrist_random_list_high32[to_r][to_c][chesstype_old_to] << 32);
		zobrist_value_new ^= (uint64_t)zobrist_random_list_low32[to_r][to_c][chesstype_old_to];
	}
	//清除原位置值
	zobrist_value_new ^= ((uint64_t)zobrist_random_list_high32[from_r][from_c][chesstype] << 32);
	zobrist_value_new ^= (uint64_t)zobrist_random_list_low32[from_r][from_c][chesstype];
	//更新目标位置值
	zobrist_value_new ^= ((uint64_t)zobrist_random_list_high32[to_r][to_c][chesstype] << 32);
	zobrist_value_new ^= (uint64_t)zobrist_random_list_low32[to_r][to_c][chesstype];

	//走完一步后,player交换
	zobrist_value_new ^= ((uint64_t)zobrist_player_high32 << 32);
	zobrist_value_new ^= (uint64_t)zobrist_player_low32;

	return zobrist_value_new;
}