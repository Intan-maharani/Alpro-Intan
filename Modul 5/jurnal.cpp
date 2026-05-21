#include<iostream>
using namespace std;



struct Tanggal{
	int tgl;
	int bln;
	int tahun;
};

struct Alamat{
	string jln;
	string kel;
	string kota;
	string prov;
	string pos;
	
};
struct Daftarp{
	long nik;
	string nama;
	Tanggal tanggal;
	char jns;
	string gol;
	long no;
	Alamat alm;
	char bpjs;
	int alergi;
	
};
void daftarpasien(Daftarp pas);
void menuUtama();
void lihatpasien();
void caripasien();
void pulangkanpasien();

int main(){
	menuUtama();
	return 0;
}

void menuUtama(){
	int pilih;
	Daftarp psn;
	while(true){
		cout<<"==================================================="<<endl;
		cout<<"        SISTEM MANAJEMEN GAZA CARE PLUS"<<endl;
		cout<<"==================================================="<<endl;
		cout<<                                            "tangal: 21/5/2026"<<endl;
		cout<<endl;
		cout<<"[1] Daftarkan Pasien baru"<<endl;
		cout<<"[2] Lihat semua Pasien"<<endl;
		cout<<"[3] Cari Pasien"<<endl;
		cout<<"[4] Pulangkan Pasien"<<endl;
		cout<<"[0] Keluar"<<endl;
		cout<<"[1] Daftarkan Pasien baru"<<endl;
		cout<<"pilihan: "; cin>>pilih;
		
		if(pilih==1){
			daftarpasien(psn);
		}
		else if(pilih==2){
			lihatpasien();
		}
		else if(pilih==3){
			caripasien();
		}
		else if(pilih==4){
			pulangkanpasien();
		}
		else if(pilih==0){
			break;
		}
		
 }
}

void daftarpasien(Daftarp pas){
	cout<<"==================================================="<<endl;
		cout<<"        PENDAFTARAN PASIEN BARU"<<endl;
		cout<<"==================================================="<<endl;
		cout<<"NIK (16 digit): ";
		cin>>pas.nik;
		cout<<"Nama: ";
		cin.ignore(1000,'\n');
		getline(cin, pas.nama);
		cout<<endl;
		cout<<"Tanggal lahir"<<endl;
		cout<<"        tanggal: ";
		cin>>pas.tanggal.tgl;
		
		cout<<"        bulan  : ";
		cin>>pas.tanggal.bln;
		cout<<"        tahun  : ";
		cin>>pas.tanggal.tahun;
		cout<<"jenis kelamin(l/p): ";
		cin>>pas.jns;
		cout<<"Gol.darah: ";
		cin>>pas.gol;
		cout<<"no.telp: ";
		cin>>pas.no;
		cout<<"Alamat: ";
		cout<<"\n    Jalan    : ";
		cin>>pas.alm.jln;
		cout<<"\n    Kelurahan: ";
		cin>>pas.alm.kel;
		cout<<"\n    Kota     : ";
		cin.ignore(1000,'\n');
		getline(cin, pas.alm.kota);
		cout<<"\n    Provinsi : ";
		cin>>pas.alm.prov;
		cout<<"\n    Pos Kode : ";
		cin>>pas.alm.pos;
		cout<<"\nPeserta BPJS(y/n): ";
		cin>>pas.bpjs;
		cout<<"\njumlah alergi(0-5): ";
		cin>>pas.alergi;
		cout<<"[ok] Pasien ID- Berhasil didaftarkan!";
		
		
		
		
}
void lihatpasien(){
	cout<<"helo";
}

void caripasien(){
	cout<<"helo";
}
void pulangkanpasien(){
	cout<<"helo";
}