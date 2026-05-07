#include<iostream>
using namespace std;
int main() {
	cout<<"[TASK 1/3] DECODE SIGNAL - COMMUNICATION ROOM"<<endl;
	cout<<"KIRIM SINYAL TERENKRIPSI DAN DESKRIPSI BALASAN DARI BUMI"<<endl;
	cout<<"[ENKRIPSI]"<<endl;
	int key;
	bool benar=true;
	while(benar){
		cout<<"masukan key: ";
		cin>>key;
		if(key>1){
			benar=false;	
		}
	}
	




	
cout<<endl;	
	cout<<"[taks 3/3] AlIGN NAVIGATION MATRIX-ENGINE CORE"<<endl;
	cout<<"<<SISTEM NAVIGASI MATO TOTAL KARENA SABOTASE"<<endl;
	cout<<"REKONSTRUKSI MATRIKS KORDINAT SEKARANG"<<endl;
	cout<<endl;
	cout<<"[MATRIKS NAVIGATION]";
	int n;
	cout<<"masukan ukuran navigation matriks (max 5): ";
	cin>> n;

		
	cout<<"matriks ganjil"<<endl;
		int angka=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				angka++;	
				if(angka%2==1){	
					if(angka<10){
						cout<<"0"<<angka<<" ";
						}
					else{
						cout<<angka<<" ";
					}
						angka++;	
			}
		}
			cout<<endl;
	}
	
	return 0;
}