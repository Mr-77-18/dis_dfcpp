#ifndef DFCPP_JSONTRAN_HPP
#define DFCPP_JSONTRAN_HPP
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <any>

using namespace std;

std::vector<std::string> type_name;

void vartypeTran(nlohmann::json& _json , void* _addr , int _next , std::string _type){
	if (_type == "i") {
		int* member = (int*)_addr;
		_json[std::to_string(_next)] = *member;
	}else if (_type == "d") {
		double* member = (double*)_addr;
		_json[std::to_string(_next)] = *member;
	}else if (_type == "x") {
		long long* member = (long long*)_addr;
		_json[std::to_string(_next)] = *member;
	}else if (_type == "St6vectorIiSaIiEE"){
		std::vector<int>* member = (std::vector<int>*)_addr;
		_json[std::to_string(_next)] = *member;
	}else{

	}
}

void vartypeTranToStruct(nlohmann::json& _json , void* _addr , int _next , std::string _type){
	if (_type == "i") {
		int* member = (int*)_addr;

		*member = _json[std::to_string(_next)];
	}else if (_type == "d") {
		double* member = (double*)_addr;

		*member = _json[std::to_string(_next)];
	}else if (_type == "x") {
		long long* member = (long long*)_addr;

		*member = _json[std::to_string(_next)];
	}else if(_type == "St6vectorIiSaIiEE"){
		vector<int>* member = (vector<int>*)_addr;

		for (auto i : _json[std::to_string(_next)]) {
			(*member).push_back(i);
		}
		//*member = _json[std::to_string(_next)];
	}{

	}
}



template <typename... Args>
struct Countmember;

template <>
struct Countmember<>{
	static const int value = 0;
};

template <typename T , typename... Args>
struct Countmember<T , Args...> {
	//type_name.push_back(typeid(T).name());
	static const int value = Countmember<Args...>::value + 1;
};

template <typename... Args>
class SendMessageImpl{
	public:
		SendMessageImpl()
			:members(Countmember<Args...>::value)
		{}

		//获取各个成员的便宜地址，保存到offset_of_struct里面
		template <typename T , typename MemberType , typename... Rest>
		void init(MemberType T::*member, Rest...);

		template <typename T , typename MemberType>
			void init(MemberType T::*member);

		const int Getnumbers(){
			return members;
		}

		//struct -> json
		template <typename T>
		void TranTojson(int _member , nlohmann::json& _json , T _next);

		template <typename T , typename... Members>
		void TranTojson(int _member , nlohmann::json& _json , T _next , Members... _other);

		//json -> struct
		template <typename T>
		void TranTostruct(int _member , nlohmann::json& _json , T& _next);

		template <typename T , typename... Members_addr>
		void TranTostruct(int _member , nlohmann::json& _json , T& _next , Members_addr&... _members_addr);

		//hold struct -> json
		template <typename T>
			void Tranhstruct(nlohmann::json& _json , T _struct);

		//hold json -> strut
		template <typename T>
			void Tranhjson(nlohmann::json& _json , T& _struct);

	private:
		//我需要知道这个类有多少个成员吧；
		int members;
		std::vector<std::size_t> offset_of_struct;
};

template <typename... Args>
template <typename T , typename... Members>
void SendMessageImpl<Args...>::TranTojson(int _member , nlohmann::json& _json , T _next , Members... _other){
	//我想依旧是使用递归实现member的转化
	if (_member > 0) {
		string name = to_string(members - _member);
		_json[name] = _next;
		TranTojson(_member - 1 , _json , _other... );
	}else{
		return;
	}
}

template <typename... Args>
template <typename T>
void SendMessageImpl<Args...>::TranTojson(int _member , nlohmann::json& _json , T _next){
	string name = to_string(members - _member);
	_json[name] = _next;
}


//要求，给出struct里面个结构体的地址
template <typename... Args>
template <typename T , typename... Members_addr>
void SendMessageImpl<Args...>::TranTostruct(int _member , nlohmann::json& _json , T& _next , Members_addr&... _members_addr){
	string name = to_string(members - _member);
	//std::cout << "::" << _member << " " <<  name << endl;
	_next = _json[name];
	TranTostruct(_member - 1 , _json , _members_addr...);
}

template <typename... Args>
template <typename T>
void SendMessageImpl<Args...>::TranTostruct(int _member , nlohmann::json& _json , T& _next){
	string name = to_string(members - _member);
	//cout << "::" << _member << " " <<  name << endl;
	_next = _json[name];
}

template <typename... Args>
template <typename T , typename MemberType , typename... Rest>
void SendMessageImpl<Args...>::init(MemberType T::*member, Rest... _rest){
	//先获取偏移地址
	std::size_t off = reinterpret_cast<std::size_t>(&(((T*)nullptr)->*member));
	//std::size_t off = offsetof(T , member);
	//cout << "off :" <<  off << endl;
	offset_of_struct.push_back(off);

	init(_rest...);
}

//最后一个偏移地址
template <typename... Args>
template <typename T , typename MemberType>
void SendMessageImpl<Args...>::init(MemberType T::*member){
	std::size_t off = reinterpret_cast<std::size_t>(&(((T*)nullptr)->*member));
	//std::size_t off = offsetof(T , member);
	//cout << "off: " << off << endl;
	offset_of_struct.push_back(off);
}

//hold struct -> json
template <typename... Args>
template <typename T>
void SendMessageImpl<Args...>::Tranhstruct(nlohmann::json& _json , T _struct){
	int i = 0;
	for (auto& off : offset_of_struct){
		void* member_addr = reinterpret_cast<void*>(reinterpret_cast<char*>(&_struct) + off);

		auto _type_name = type_name.at(i);

		vartypeTran(_json , member_addr , i  , _type_name);

		i++;
	}
}

//这个函数的作用就是把_json里面的字段复制给struct
template <typename... Args>
template <typename T>
void SendMessageImpl<Args...>::Tranhjson(nlohmann::json& _json , T& _struct){
	//取得_struct里面各个成员的便宜地址，然后再转过去呗
	int i = 0;
	for (auto& off : offset_of_struct) {
		void* member_addr = reinterpret_cast<void*>(reinterpret_cast<char*>(&_struct) + off);

		auto _type_name = type_name.at(i);

		vartypeTranToStruct(_json , member_addr , i  , _type_name);

		i++;
	}

}

#endif


