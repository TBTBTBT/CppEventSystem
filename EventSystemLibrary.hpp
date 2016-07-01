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
 
 特徴は、引数の個数と種類に制限がないことだと思います。
 
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
 
 なお、例ではint,charとしていますが、引数の個数、種類は自由です。
 
 2.
 イベントに関数を登録します。（？）
 AddListenerメソッドを使います。
 
 eventTest.AddListener("イベント名",登録する関数ポインタ);
 
 
 というようにします。
 
 
 3.
 イベントを実行します。
 Invokeメソッドを使います。
 
 
 例:引数を持たせない場合
  eventTest.Invoke("イベント名")
 
 例:引数を持たせる場合は
  eventTest.Invoke("イベント名",引数,引数...);
 
 
 というようにします。
 
 
 機能
 EventManagerクラス
 EventManager::AddEvent(string 名前,void );

*/

//可変長テンプレートで実装するのだ
namespace EventSystemLibrary{
    template<typename... T>
    class Event {
    private:
        std::vector< std::function< void (T...) > > func;
    public:
        void Invoke(T...);
        void AddListener(void(*f)(T...));
        ~Event();
    };
    template<typename... T>
    class EventManager {
    private:
        std::map< std::string, Event<T...> > events;
    public:
        
        void AddListener(std::string,void(*f)(T...));
        void Invoke(std::string,T...);
        ~EventManager();
    };
    
    template<typename... T>
    void Event<T...>::Invoke(T... t) {
        for (int i = 0; i < func.size(); i++) {
            func[i](t...);
        }
    }
    template<typename... T>
    void Event<T...>::AddListener(void(*f)(T...)) {
        func.push_back(f);
    }
    template<typename... T>
    Event<T...>::~Event() {
        func.clear();
    }
    
    template<typename... T>
    void EventManager<T...>::AddListener(std::string  name, void(*f)(T...)){
        events[name].AddListener(f);
    }
    template<typename... T>
    void EventManager<T...>::Invoke(std::string name,T... t) {
        return events[name].Invoke(t...);
    }
    template<typename... T>
    EventManager<T...>::~EventManager(){
        events.clear();
    }
}
/*
 
 誰かに褒められたい

 */
#pragma GCC visibility pop
#endif
