#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"


// ノードを初期化
void initialize_node(node* p, int val)
{
	p->pNext = NULL;
	p->pPrev = NULL;
	p->data = val;
}

// リストを初期化
void initialize_list(list* l)
{
	l->header = NULL;
	l->footer = NULL;
}


// 先頭にデータを追加
void push_front(list* l, node* p){
	if (!l || !p) return; //リストとノードが存在しなければ終了する。
	p->pPrev = NULL; //先頭であるから初期化(＝前のノードは存在しないことになる。)
	p->pNext = l->header; //元の先頭を'p'の次に。
	
	if (l->header) l->header->pPrev = p; //リストにノードがある場合、先頭のノードを'p'の後ろに。
	else l->footer = p; //リストが空ならfooterも'p'に。
	l->header = p; //リストの先頭を'p'に。
}

// 末尾にデータを追加
void push_back(list* l, node* p){
	if (!l || !p) return; //同様に存在しなければ終了。
	p->pNext = NULL; //末尾に挿入され、続きはないのでNULLにする。
	p->pPrev = l->footer; //元の末尾を前に。

	if (l->footer) l->footer->pNext = p; //リストにノードがあるなら、末尾のノードの次を'p'に。
	else l->header = p; //リストが空ならheaderも'p'に。
	l->footer = p; //リストの末尾を'p'に。
}

// pのノードを削除
void remove_node(list* l, node* p){
	if (!l || !p) return; //同様に(以下略)
	// pの前にノードがある場合、その次を'p'の次へ繋ぎ直す(pをリストから除外)。
	if (p->pPrev) p->pPrev->pNext = p->pNext;
	else l->header = p->pNext; //(p->pPrev == NULL)ならheaderを'p'の次に。

	// pの次にノードがある場合、その前を'p'の前に繋ぐ。
	if (p->pNext) p->pNext->pPrev = p->pPrev;
	else l->footer = p->pPrev; //(p->pNext == NULL)footerを一つ前に。
	
	p->pNext = NULL; //ポインタを完全に外す。
	p->pPrev = NULL;
}

// remove_node()の処理を利用して、'p'の左右にあるノードを削除する。
// pの次のノードを削除
void remove_next(list* l, node* p){
	if (!l || !p) return; //(略)
	if (!p->pNext) return; //次が無ければ終了。
	remove_node(l, p->pNext); //対象のノードをremove_node()で処理。
}
// pの前のノードを削除
void remove_prev(list* l, node* p){
	if (!l || !p) return; //(略)
	if (!p->pPrev) return; //前がなければ終了。
	remove_node(l, p->pPrev); //同様にremove_node()で処理。
}


// pの次のノードを取得
node* get_next(list* l, node* p){
	if (!p) return NULL;
	return p->pNext;
}

// pの前のノードを取得
node* get_prev(list* l, node* p){
	if (!p) return NULL;
	return p->pPrev;
}
