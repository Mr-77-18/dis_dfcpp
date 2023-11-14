//struct data{
//	int ;
//	double;
//	...
//}
//
//send = jsondata(struct data);
//
//send.send(int  , double ,);
//
//send(){
//	json[] = int ;
//	json[] = double;
//	...;
//
//
//	any->message;
//}
#ifndef DFCPP_JSONTRAN_HPP
#define DFCPP_JSONTRAN_HPP
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;

template <typename... Args>
struct Countmember;

template <>
struct Countmember<>{
	static const int value = 0;
};

template <typename T , typename... Args>
struct Countmember<T , Args...> {
	static const int value = Countmember<Args...>::value + 1;
};

template <typename... Args>
class SendMessageImpl{
	public:
		SendMessageImpl()
			:members(Countmember<Args...>::value)
		{}

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

	private:
		//我需要知道这个类有多少个成员吧；
		int members;
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
	cout << "::" << _member << " " <<  name << endl;
	_next = _json[name];
	TranTostruct(_member - 1 , _json , _members_addr...);
}

template <typename... Args>
template <typename T>
void SendMessageImpl<Args...>::TranTostruct(int _member , nlohmann::json& _json , T& _next){
	string name = to_string(members - _member);
	cout << "::" << _member << " " <<  name << endl;
	_next = _json[name];
}

#endif

//example:
//struct Mydata{
//	int a;
//	double b;
//};
//
//int main(int argc, char *argv[])
//{
//	struct Mydata data = {1 , 1.2};
//
//	SendMessageImpl<int , double , string> sm;
//	cout << sm.Getnumbers() << endl;
//
//	nlohmann::json _json;
//	sm.TranTojson(sm.Getnumbers() , _json , data.a , data.b);
//
//	cout << _json["0"]  << " " << _json["1"] << endl;
//
//	struct Mydata copy;
//
//	sm.TranTostruct(sm.Getnumbers() , _json , copy.a , copy.b);
//
//	cout << copy.a << " " << copy.b << endl;
//
//	return 0;
//}
