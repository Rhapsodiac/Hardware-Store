#pragma once
#define Product_H
#ifdef Product_H

#include <string.h>
#include <sstream>
#include <iomanip>

using std::setw;
using std::left;
using std::stringstream;
using std::string;

class Product{
public:
	char* stockNum;
	int quant;
	char* name;
	double price;

public:
	Product(char*, int, char*, double);
	//Product(const Product &obj, int);
	//char * test();

	int getQuant(){
		return quant;
	}
	void setQuant(int q){
		quant = q;
	}
	char* getStockNum(){
		return stockNum;
	}
	double getPrice(){
		return price;
	}
	char* getName(){
		return name;
	}

	bool operator <= (const Product& obj) const{
		int res = strcmp(name, obj.name);
		return(res < 0 || res == 0);
	}
	
	bool operator == (const Product& obj) const{
		return (stockNum == obj.stockNum ? true : false);
	}

	CStringW getNameDisplay(){
		char* myStr = NULL;
		myStr = name;
		return getWCHAR(myStr);

		/*
		size_t s = strlen(myStr) + 1;
		const size_t s2 = 100;
		size_t converted = 0;
		wchar_t wcstring[s2];
		mbstowcs_s(&converted, wcstring, s, myStr, _TRUNCATE);
		return wcstring;
		*/
	}

	CStringW getStockNumDisplay(){
		char* myStr = NULL;
		myStr = stockNum;
		return getWCHAR(myStr);
	}

	CStringW getQuantDisplay(){
		const char* myStr = NULL;
		stringstream ss1("");
		ss1 << quant << '\t';
		string s = ss1.str();
		myStr = s.c_str();
		return getWCHAR(myStr);
	}

	CStringW getPriceDisplay(){
		const char* myStr = NULL;
		stringstream ss("");
		ss << "$";
		ss << std::fixed << std::setprecision(2);
		ss << price;
		string s2 = ss.str();
		myStr = s2.c_str();
		return getWCHAR(myStr);
	}

	CStringW getFullDisplay(){
		const char* myStr = NULL;
		const char* s_quant = NULL;
		const char *s_price = NULL;
		char *temp = NULL;

		/*

		//quant(int) to const char*
		std::stringstream ss1("");
		ss1 << quant << '\t';
		std::string s = ss1.str();
		s_quant = s.c_str();

		//price(double) to const char*
		std::stringstream ss2("");
		ss2 << price;
		std::string s2 = ss2.str();
		s_price = s2.c_str();
		
		//create full string with spacing
		myStr = name + '\t';
		strcat(myStr, s_quant);
		strcat(myStr, s_quant);
		strcat(myStr, s_price);

		*/

		stringstream ss3("");
		ss3 << left;
		ss3 << setw(10);
		ss3 << stockNum ;
		ss3 << setw(10);
		ss3 << quant;
		ss3 << setw(20);
		ss3 << name ;
		ss3 << setw(10);
		ss3 << price;
		string s3 = ss3.str();
		myStr = s3.c_str();

		return getWCHAR(myStr);
	}

	CStringW getWCHAR(const char* myStr){
		size_t s = strlen(myStr) + 1;
		const size_t s2 = 200;
		size_t converted = 0;
		wchar_t wcstring[s2];
		mbstowcs_s(&converted, wcstring, s, myStr, _TRUNCATE);
		return wcstring;
	}

	CStringW getOutOfStock(){
		const char* myStr;
		stringstream ss("");
		ss << left;
		ss << "OUT OF STOCK - QUANTITY IS BACKORDERED";
		string s3 = ss.str();
		myStr = s3.c_str();
		return (getWCHAR(myStr));
	}
};

inline Product::Product(char* s, int q, char* n, double p){
	stockNum = s;
	quant = q;
	name = n;
	price = p;
}

//inline Product::Product(const Product &obj, int q){
//	stockNum = obj.stockNum;
//	quant = q;
//	name = obj.name;
//	price = obj.price;
//}

//inline char* Product::test(){
//	return name;
//}

inline std::ostream & operator << (std::ostream & Str, Product const & v){
	if (v.name != NULL){
		Str << v.name;
		return Str;
	}
}
#endif