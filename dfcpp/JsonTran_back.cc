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
//#ifndef DFCPP_JSONTRAN_HPP
//#define DFCPP_JSONTRAN_HPP
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>

using namespace std;

std::vector<std::string> type_name;
//i代表第几个结构体成员
//template <typename T>
auto typefunction(void* _addr , std::string _type_name){
//	switch (_type_name) {
//		case "i":
//			return *(int*)_addr;
//		case "d":
//			return *(double*)_addr;
//		default:
//			break;
	//}
	return 1;
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

template <typename... Args>
template <typename T , typename MemberType , typename... Rest>
void SendMessageImpl<Args...>::init(MemberType T::*member, Rest... _rest){
	//先获取偏移地址
	std::size_t off = reinterpret_cast<std::size_t>(&(((T*)nullptr)->*member));
	//std::size_t off = offsetof(T , member);
	cout << "off :" <<  off << endl;
	offset_of_struct.push_back(off);

	init(_rest...);
}

//最后一个偏移地址
template <typename... Args>
template <typename T , typename MemberType>
void SendMessageImpl<Args...>::init(MemberType T::*member){
	std::size_t off = reinterpret_cast<std::size_t>(&(((T*)nullptr)->*member));
	//std::size_t off = offsetof(T , member);
	cout << "off: " << off << endl;
	offset_of_struct.push_back(off);
}

//hold struct -> json
template <typename... Args>
template <typename T>
void SendMessageImpl<Args...>::Tranhstruct(nlohmann::json& _json , T _struct){
	int i = 0;
	for (auto& off : offset_of_struct){
		//cout << &_struct + off << endl;
		void* member_addr = reinterpret_cast<void*>(reinterpret_cast<char*>(&_struct) + off);
		auto _member = typefunction(member_addr , type_name.at(i));
		_json[std::to_string(i)] = _member;
	}
}

//#endif

//example:
struct Mydata{
	int a;
	double b;
};

int main(int argc, char *argv[])
{
	struct Mydata data = {1 , 1.2};

	SendMessageImpl<int , double , string> sm;//成员个数
	sm.init(&Mydata::a , &Mydata::b);//偏移地址
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
//	cout << "lst" << endl;
//	sm.Tranhstruct(data);
//
	type_name.push_back(typeid(int).name());
	type_name.push_back(typeid(double).name());

	nlohmann::json _json;
	sm.Tranhstruct(_json , data);

	return 0;
}
