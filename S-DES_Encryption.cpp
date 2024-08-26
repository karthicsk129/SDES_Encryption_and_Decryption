#include <iostream>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
using namespace std;


void Keygen(bitset<10> key0, bitset<8> *key1, bitset<8> *key2){
    //now finding the permuted key!
    bitset<10> p10;
    p10[9]=key0[2];
    p10[8]=key0[4];
    p10[7]=key0[1];
    p10[6]=key0[6];
    p10[5]=key0[3];
    p10[4]=key0[9];
    p10[3]=key0[0];
    p10[2]=key0[8];
    p10[1]=key0[7];
    p10[0]=key0[5];
    
    //splitting into left and right half
    bitset<5> left1;
    bitset<5> right1;
    for(int i=9;i>4;i--){
        left1[i-5]=p10[i];
        right1[i-5]=p10[i-5];
    }
    bitset<5> sleft1=left1<<1 | left1 >> (5 - 1);
    bitset<5> sright1=right1<<1 | right1 >> (5 - 1);

    bitset<10> comb_ls1;
    for(int i=9;i>4;i--){
        comb_ls1[i]=sleft1[i-5];
    }
    for(int i=9;i>4;i--){
        comb_ls1[i-5]=sright1[i-5];
    }

    bitset<8> p8_1;
    p8_1[7]=comb_ls1[9-5];
    p8_1[6]=comb_ls1[9-2];
    p8_1[5]=comb_ls1[9-6];
    p8_1[4]=comb_ls1[9-3];
    p8_1[3]=comb_ls1[9-7];
    p8_1[2]=comb_ls1[9-4];
    p8_1[1]=comb_ls1[9-9];
    p8_1[0]=comb_ls1[9-8];
    
    *key1=p8_1;
    
    
    bitset<5> sleft2_1=sleft1<< 1 | sleft1 >> (5 - 1);
    bitset<5> sleft2_2=sleft2_1<< 1 | sleft2_1 >> (5 - 1);
    bitset<5> sright2_1=sright1<< 1 | sright1 >> (5 - 1);
    bitset<5> sright2_2=sright2_1<< 1 | sright2_1 >> (5 - 1);
    
    
    
    bitset<10> comb_ls2;
    for(int i=9;i>4;i--){
        comb_ls2[i]=sleft2_2[i-5];
    }
    for(int i=9;i>4;i--){
        comb_ls2[i-5]=sright2_2[i-5];
    }
   
    
    bitset<8> p8_2;
    p8_2[7]=comb_ls2[9-5];
    p8_2[7]=comb_ls2[9-2];
    p8_2[5]=comb_ls2[9-6];
    p8_2[4]=comb_ls2[9-3];
    p8_2[3]=comb_ls2[9-7];
    p8_2[2]=comb_ls2[9-4];
    p8_2[1]=comb_ls2[9-9];
    p8_2[0]=comb_ls2[9-8];
    
    *key2=p8_2;

}
bitset<4> sbox(bitset<8> exor1){
    
    int sbox1[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,0,2}};
    int sbox2[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,2},{2,1,0,3}};
    
    bitset<4> sb1;
    bitset<4> sb2;
    
    for(int i=7;i>3;i--){
        sb1[i-4]=exor1[i];
        sb2[i-4]=exor1[i-4];}
    
    bitset<2> row1;
    row1[1]=sb1[3];
    row1[0]=sb1[0];
    
    bitset<2> col1;
    col1[1]=sb1[2];
    col1[0]=sb1[1];
    
    unsigned long rowval1 = row1.to_ulong();
    unsigned long colval1 = col1.to_ulong();
    
    bitset<2> h1(sbox1[rowval1][colval1]);
    
    bitset<2> row2;
    row2[1]=sb2[3];
    row2[0]=sb2[0];
    
    bitset<2> col2;
    col2[1]=sb2[2];
    col2[0]=sb2[1];
    
    unsigned long rowval2 = row2.to_ulong();
    unsigned long colval2 = col2.to_ulong();
    
    bitset<2> h2(sbox2[rowval2][colval2]);
    
    bitset<4> sbout_1;
    sbout_1[3]=h1[1];
    sbout_1[2]=h1[0];
    sbout_1[1]=h2[1];
    sbout_1[0]=h2[0];
    
    return sbout_1;
    
}
int main()
{
    //Getting the Plain text and Key as Input
    bitset<10> key;
    bitset<8> pt;
    cout<<"Enter the key:";
    cin>>key;
    cout<<"Enter the Plain Text:";
    cin>>pt;
    
    
    
    bitset<8> key1,key2;
    
    Keygen(key, &key1, &key2);
    

    
    
    cout<<"Starting the Encryption..."<<endl;
        //Sending PT to IP box
    
    
    
    string bit_str = pt.to_string();

    // Reverse the string
    std::reverse(bit_str.begin(), bit_str.end());

    // Create a new bitset from the reversed string
    bitset<8> pt1(bit_str); //Our modified plaintext according to bitset

    bitset<8> ip; //Initial Permutation Box
    ip[7]=pt1[1];
    ip[6]=pt1[5];
    ip[5]=pt1[2];
    ip[4]=pt1[0];
    ip[3]=pt1[3];
    ip[2]=pt1[7];
    ip[1]=pt1[4];
    ip[0]=pt1[6];
    
    //Starting of Round 1
    //splitting the IP box Output
    bitset<4> li1;
    bitset<4> ri1;
    
    for(int i=7;i>3;i--){
        li1[i-4]=ip[i];
        ri1[i-4]=ip[i-4];
    }

    
    //Sending the right half to Expansion PBOX
    
    bitset<8> ep1;
    ep1[7]=ri1[3-3];
    ep1[6]=ri1[3-0];
    ep1[5]=ri1[3-1];
    ep1[4]=ri1[3-2];
    ep1[3]=ri1[3-1];
    ep1[2]=ri1[3-2];
    ep1[1]=ri1[3-3];
    ep1[0]=ri1[3-0];
    

    
    bitset<8> exor1= ep1 ^ key1;
    
    bitset<4> sbout1;
    sbout1=sbox(exor1); //Obtaining values from SBOX Function

    //P4 box
    bitset<4> p4_1;
    p4_1[3]=sbout1[4-2];
    p4_1[2]=sbout1[4-4];
    p4_1[1]=sbout1[4-3];
    p4_1[0]=sbout1[4-1];

    
    bitset<4> ri2;
    ri2= p4_1 ^ li1;
    bitset<8> ep2;

    //Starting the Round 2 Operations
    ep2[7]=ri2[3-3];
    ep2[6]=ri2[3-0];
    ep2[5]=ri2[3-1];
    ep2[4]=ri2[3-2];
    ep2[3]=ri2[3-1];
    ep2[2]=ri2[3-2];
    ep2[1]=ri2[3-3];
    ep2[0]=ri2[3-0];
    
    bitset<8> exor2;
    exor2= ep2 ^ key2;
    bitset<4> sbout2;
    sbout2=sbox(exor2);
    
    bitset<4> p4_2;
    p4_2[3]=sbout2[4-2];
    p4_2[2]=sbout2[4-4];
    p4_2[1]=sbout2[4-3];
    p4_2[0]=sbout2[4-1];
    
    bitset<4> lf,rf;
    lf= p4_2 ^ ri1;
    rf= ri2;
    
    bitset<8> fin;
    for(int i=7;i>3;i--){
        fin[i]=lf[i-4];
        fin[i-4]=rf[i-4];
    }


    //Final Permutation takes place
    bitset<8> fpbox;
    fpbox[7]=fin[8-4];
    fpbox[6]=fin[8-1];
    fpbox[5]=fin[8-3];
    fpbox[4]=fin[8-5];
    fpbox[3]=fin[8-7];
    fpbox[2]=fin[8-2];
    fpbox[1]=fin[8-8];
    fpbox[0]=fin[8-6];
    
    
    
    cout<<"Cipher Text: "<< fpbox<<endl;
}
