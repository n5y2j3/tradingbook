본문 바로가기
할일목록 바로가기
주메뉴 바로가기
하단 바로가기
홈으로
마이페이지 바로가기
쪽 지 0
common.home.alt.picture
나예지
개인정보수정
로그아웃
블록체인 스페셜리스트 양성과정 

강의 계획서
학습 목차
학습 정보
학습 활동
학습 현황
과목 정보
성적
할 일 목록이 없습니다
학습 정보홈으로강의실블록체인 스페셜리스트 양성과정학습 정보자료실
공지사항
질의응답
자료실
상담게시판
 
search 글쓰기 글쓰기 홈 학습목차
  new trading book  상 세 작성자 : 산단교수2 작성일 : 2019-07-23조회수 : 0
#include
#include

using namespace eosio;

CONTRACT tradingbook: public contract {
public:
using contract::contract;

ACTION dummy() {}

[[eosio::on_notify("eosio.token::transfer")]]
void ontransfer(name from, name to, asset quantity, std::string memo) {
if(from == get_self()) {
Receive forReceiver(get_self(), get_self().value);
forReceiver.emplace(get_self(), [&](auto& row) {
row.mykey = forReceiver.available_primary_key();
row.user = from;
row.balance = quantity;
});
} else {
Send forSender(get_self(), get_self().value);
forSender.emplace(get_self(), [&](auto& row) {
row.mykey = forSender.available_primary_key();
row.user = to;
row.balance = quantity;
});
}
}
private:
TABLE tradingbook_struct {
uint64_t mykey;
name user;
asset balance;

uint64_t primary_key() const { return mykey; }
};

typedef multi_index<"senderbook"_n, tradingbook_struct> Send;
typedef multi_index<"receiverbook"_n, tradingbook_struct> Receive;
};