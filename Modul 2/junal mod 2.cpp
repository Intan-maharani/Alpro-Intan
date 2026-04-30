#include<iostream>
using namespace std;
int main () {
	int umur,perlindungan=3;
	bool kondisi=true;
	char huruf;
	
cout<<"===GOBLET OF FIRE: TRURNAMEN OF TRIWIZARD==="<<endl;
cout<<"masukan umur anda: ";
cin>>umur;
if(umur>=17){
cout<<"Piala api menyala! anda terpilih sebagai triwizard champion"<<endl;;
}
else{
	cout<<"piala api menolak anda! umur terlalu kecil"<<endl;;
	kondisi=false;
}

//tugas satu 
while (kondisi){
cout<<"---Tugas satu Naga Hungarian Horntail---"<<endl;;
if(perlindungan>0){
cout<<"sisa perlindungan sihir: "<<perlindungan<<endl;;
cout<<"pilih strategi(a: sembunyi, b: panggil sapu)";
cin>>huruf;
switch (huruf){
	case 'a':		
cout<<"Naga menyemburkan api! anda terluka"<<endl;;
cout<<"sisa perlindungan sihir: "<<(perlindungan-1)<<endl;
break;

	case 'b':
cout<<"Berhasil! anda mengambil telur emas"<<endl;;
kondisi=false;

	default:
cout<<"pilihan tidak valid ulangi pilihan"<<endl;;
}

}
else{
cout<<"kesempatan habis! anda di tarik keluar arena oleh pawang naga"<<endl;;
}

}

//tugas 2 danau hitam
cout<<"---tugas 2 Danau Hitam---"<<endl;;
int menit=0;
char aksi;
bool keadaan=true;
while(menit<60){
while(!keadaan){

cout<<"menit 10... ada Grindylow! (l: lawan, h: hindari): "<<endl;
cin>>aksi;

if(aksi=='h'){
cout<<"lolos dari Grindylow"<<endl;
menit+=10;
}
else if(aksi=='l'){
cout<<"oksigen anda habis karena kelelahan bertarung"<<endl;
continue;
}

else{
cout<<"pilihan tidak valid! ulangi pilihan"<<endl;
keadaan=false;
}

}


while(!kondisi){
cout<<"menit 20... ada Grindylow! (l: lawan, h: hindari): "<<endl;
cin>> aksi;
if(aksi=='h'){
cout<<"lolos dari Grindylow"<<endl;
menit+=10;
}
else if(aksi=='l'){
cout<<"oksigen anda habis karena kelelahan bertarung"<<endl;
continue;
}

else{
cout<<"pilihan tidak valid! ulangi pilihan"<<endl;
keadaan=false;
}
}
while(!kondisi){
cout<<"menit 30... ada Grindylow! (l: lawan, h: hindari): "<<endl;
cin>> aksi;
if(aksi=='h'){
cout<<"lolos dari Grindylow"<<endl;
menit+=10;
}
else if(aksi=='l'){
cout<<"oksigen anda habis karena kelelahan bertarung"<<endl;
continue;
}

else{
cout<<"pilihan tidak valid! ulangi pilihan"<<endl;
keadaan=false;

}
}
while(!kondisi){
cout<<"menit 40... ada Grindylow! (l: lawan, h: hindari): "<<endl;
cin>> aksi;
if(aksi=='h'){
cout<<"lolos dari Grindylow"<<endl;
menit+=10;
}
else if(aksi=='l'){
cout<<"oksigen anda habis karena kelelahan bertarung"<<endl;
continue;
}

else{
cout<<"pilihan tidak valid! ulangi pilihan"<<endl;
keadaan=false;

}
}

while(!kondisi){
cout<<"menit 50... ada Grindylow! (l: lawan, h: hindari): "<<endl;
cin>> aksi;
if(aksi=='h'){
cout<<"lolos dari Grindylow"<<endl;
menit+=10;
}
else if(aksi=='l'){
cout<<"oksigen anda habis karena kelelahan bertarung"<<endl;
continue;
}

else{
cout<<"pilihan tidak valid! ulangi pilihan"<<endl;
keadaan=false;

}
}

cout<<"Tepat 60 menit anda menyelamatkan sandera: "<<endl;
}
	return 0;
}