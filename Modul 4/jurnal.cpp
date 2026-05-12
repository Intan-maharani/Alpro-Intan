#include<iostream>
using namespace std;



//varian function
void header();
void menuutama();
void headerstore();
void headerkalku();
void bersih();



int main(){
	
	return 0;
}

void header(){
	cout<<"==================================="<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"[       MODULE 4 - FUNCTION       ]"<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"==================================="<<endl;
	
}

void bersih(){
	system("cls");
	system("pause");
}

void menuutama(){
	int pilih;
	header();
	cout<<"1.TIVAIZ store\n2.kalkulator TIVAIZ\n0.keluar"<<endl;
	cout<<"=============================================="<<endl;
	cout<<"pilih menu: "; cin>>pilih;
	
	if(pilih==1){
		tivstore();
	}
	else if(pilih==2){
		tivkalkulator();
	}
	else{
		break;
	}
}

void headerstore(){
	cout<<"#===========================#"<<endl;
	cout<<"|         TIVAIZ STORE      |"<<endl;
	cout<<"#===========================#"<<endl;
}

void headerkalku(){
	cout<<"+===========================-"<<endl;
	cout<<"|     TIVAIZ KALKULATOR     |"<<endl;
	cout<<"x===========================/"<<endl;
}

void tivstore(){
	int sub;
	system("cls");
	while(true){
		headerstore();
		cout<<"1.Input Barang\n2.Hapus Barang\n3.Edit Barang\n4.Lihat Barang\n0.Kembali"<<endl;
		cout<<"=============================================="<<endl;
		cout<<"pilih menu: "; cin>>sub;
	
		if(sub==1){
		inputbrg();
		}
		else if(sub==2){
		hapusbrg();
		}
		else if(sub==3){
		editbrg();
		}
		else if(sub==4){
		lihatbrg();
		}
		else if(sub==0){
		break;	
		}
		else{
		cout<<"input tidak valid";
		system("pause");
	}
	
 }
}

void inputbrg(){
	header();
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"        INPUT BARANG         "<<endl;
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"Nama Barang: ";
	cin.ignore();
	getline(cin, barang);
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"Stok (unit): "
	int stok; cin>>stok;
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"harga: "; cin>>harga;
	int tb=0
	tb+=1;
	if(stok!=""){
		cout<<"[Berhasil]" <<barang<<" Ditambahkan! "<<"(Total barang: "<< tb<<")"<<endl;
		
	}
	else{
		cout<<"input tidak valid"<<endl;
	}
	
}

void hapusbrg(){
	while(true){
	int no=1;
	no+=1;
	header();
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"        HAPUS BARANG         "<<endl;
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"no/t:"<<no<<endl;
	cout<<"Nama barang/t: "<<endl;
	int jumlahbarg(int &barang){
	return barang--;
   }
    cout<<"Harga barang\t: "<<endl;cin>>harga;
    
 }
}

void tivkalkulator(){
	while(true){
		int pilih;
		headerkalku();
		cout<<"1.oprasi dasar (+, -, *, /)\n2.faktorial\n0.kembali"<<endl;
		cout<<"=============================================="<<endl;
		cout<<"pilih menu: "; cin>>pilih;
		
		if(pilih==1){
			opdas();
		}
		else if(pilih==2){
			faktorial();
		}
		else{
			break;
		}
	
  }
	
}

void opdas(){
	headerkalku();
	string operator;
	cout<<endl;
	cout<<"operator(+, -, *, /,): "<<endl;
	cin>>operator;
	if(operator=="+"){
		
	}
	
}

