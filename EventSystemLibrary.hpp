/*
 *  EventSystemLibrary.hpp
 *  EventSystemLibrary
 *
 *  Created by Shogo Tabata on 2016/07/01.
 *  Copyright © 2016年 Shogo Tabata. All rights reserved.
 *
 */

#ifndef EventSystemLibrary_
#define EventSystemLibrary_

/* The classes below are exported */
#pragma GCC visibility push(default)
#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <map>
/*
 名称:
 イベントシステムライブラリ
 
 namespace:
 EventSystemLibrary
 
 
 概要
 
 c++で擬似イベントシステムを使用するためのライブラリです。
 ゲーム開発などに使えると思います。
 使い方は下記を参照してください。
 基本的にはUnityのUnityEventににてると思います。
 
 特徴は、
 
 ・引数の個数が7つまでであること
 ・関数の指定に文字列を使うこと
 
 です。
 プログラミング初級者ですので、危険なところや、表現に誤りがあるかもしれません。
 詳しい方、アドバイスお願いいたします。
 
 
 使い方
 
 
 1.
 EventManager のインスタンスを作成します。
 例:引数を持たせない場合
 EventManager<> eventTest
 
 例:引数を持たせる場合は
 EventManager<int> eventTest
 EventManager<int,char> eventTest
 
 なお、例ではint,charとしていますが、引数の個数は7つまで、種類は自由です。
 
 2.
 イベントに関数を登録します。（？）
 AddListenerメソッドを使います。
 
 eventTest.AddListener("イベント名",登録するメンバ関数ポインタ,メンバを持つインスタンス,引数の数だけ_ARG);
 
 
 というようにします。
 
 引数の数だけ_ARGとありますが、たとえば
 A クラスのインスタンス a が持つ、
 a.Test(int,int,char);
 という関数を登録する場合
 
 eventTest.AddListener("OnClick",&A::Test,a,_Arg,_Arg,_Arg);
 
 となります。
 
 
 3.
 イベントを実行します。
 Invokeメソッドを使います。
 
 
 例:引数を持たせない場合
  eventTest.Invoke("イベント名")
 
 例:引数を持たせる場合は
  eventTest.Invoke("イベント名",引数,引数...);
 
 
 というようにします。
 
 
 機能
 
 
 コピペ用
 #include "EventSystemLibrary.hpp"
 
*/

#define RETURN(x) -> decltype(x) { return x; }
#define BINDSINTAX1 template<class LC,typename F = void (LC::*)(T...)> auto binding(F bf,LC * ins
#define _ARG 0

namespace EventSystemLibrary{
    using namespace std::placeholders;//_1 _2で引数が呼べるように
    
    
    //イベントに登録された関数を管理するクラス
    
    
    template<typename... T>
    class Event {
    private:
        std::vector< std::function< void (T...) > > func;
        BINDSINTAX1 ,int ) RETURN ( std::bind(bf,ins,_1))
        BINDSINTAX1 ,int,int ) RETURN ( std::bind(bf,ins,_1,_2))
        BINDSINTAX1 ,int,int,int ) RETURN ( std::bind(bf,ins,_1,_2,_3))
        BINDSINTAX1 ,int,int,int,int ) RETURN ( std::bind(bf,ins,_1,_2,_3,_4))
        BINDSINTAX1 ,int,int,int,int,int ) RETURN ( std::bind(bf,ins,_1,_2,_3,_4,_5))
        BINDSINTAX1 ,int,int,int,int,int,int ) RETURN ( std::bind(bf,ins,_1,_2,_3,_4,_5,_6))
        BINDSINTAX1 ,int,int,int,int,int,int,int ) RETURN ( std::bind(bf,ins,_1,_2,_3,_4,_5,_6,_7))
    public:
        void Invoke(T... t){
            for (int i = 0; i < func.size(); i++) {
                func[i](t...);
            }
        }
        template<class LC,typename F = void (LC::*)(T...),typename... I>
        void AddListener(F bf,LC * ins,I... i){
            std::function< void (T...) > f = binding<LC>(bf,ins,i...);
            func.push_back(f);
        }
        void AddListener(void (*f)(T...)){
            func.push_back(f);
        }
        ~Event(){ func.clear(); }
    };
    
    
    //Eventをコンテナで管理するクラス
    
    
    template <typename... T>
    class EventManager {
    private:
        std::map< std::string, Event<T...> > events;
    public:
        template <class LC,typename F = void (LC::*)(T...),typename... I>
        void AddListener(std::string name,F f,LC * ins, I... i){ events[name].template AddListener<LC>(f,ins,i...); }
        void AddListener(std::string name,void (*f)(T...))     { events[name].AddListener(f); }
        void Invoke(std::string name,T... t)                   { events[name].Invoke(t...); }
        ~EventManager(){ events.clear(); }
    };

}

        //line130 events[name].template AddListener<LC>(f,ins,i...); <- なぜtemplateが必要なのかわからない
/*
 
 誰かに褒められたい

 */
#pragma GCC visibility pop
#endif
