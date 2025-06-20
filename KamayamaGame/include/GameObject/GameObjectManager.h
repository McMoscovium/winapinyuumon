#pragma once

#include <vector>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "GameObject/PictureObject.h"
#include "GameObject/TextObject.h"
#include "GameObject/GameObject.h"
#include <type_traits>


class GameObjectManager
{
private:
	struct ObjectEntry {
		std::unique_ptr<GameObject> object;
		std::type_index type;
	};
	std::unordered_map<std::string, ObjectEntry> objects;
	std::vector<std::string> drawOrder;

public:
	GameObjectManager() = default;
	//ムーブコンストラクタ
	GameObjectManager(GameObjectManager&& src) noexcept {
		if (this != &src) {
			objects = std::move(src.getObjects());
			drawOrder = src.getDrawOrderDirect();
		}
	}

	//コピー代入演算子（所有権を移動）
	GameObjectManager& operator=(GameObjectManager&& src)noexcept {
		if (this != &src) {
			objects = std::move(src.getObjects());
			drawOrder = src.getDrawOrderDirect();
		}
		return *this;
	}

	// コピーは許可しない
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;

	~GameObjectManager() = default;

	//オブジェクトを手前に追加
	template <typename T, typename... Args>
	T& addFront(const std::string& name, Args&&...args) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		if (objects.find(name) != objects.end()) {
			//すでにnameと同じ名前のオブジェクトをもつ
			throw std::runtime_error("同じ名前のオブジェクトが既にあります: " + name);
		}
		objects.emplace(name, ObjectEntry{ std::make_unique<T>(name, std::forward<Args>(args)...), std::type_index(typeid(T)) });
		drawOrder.push_back(name);
		return getObject<T>(name);
	}

	//右辺値参照を受け取って直接追加
	template <typename T>
	T& addFrontDirect(const std::string& name, std::unique_ptr<T>&& object) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		if (objects.find(name) != objects.end()) {
			//すでにnameと同じ名前のオブジェクトをもつ
			throw std::runtime_error("同じ名前のオブジェクトが既にあります: " + name);
		}
		objects.emplace(name, ObjectEntry{ std::move(object),std::type_index(typeid(T)) });
		drawOrder.push_back(name);
		return getObject<T>(name);
	}
	
	//描画順に並べたGameObject&型参照のリストを返す
	std::vector<std::reference_wrapper<GameObject>> getDrawOrder()const {
		std::vector<std::reference_wrapper<GameObject>> result;
		for (const auto& name : drawOrder) {
			result.push_back(*objects.at(name).object);
		}
		return result;
	}

	//描画順に並べたリストをそのまま返す
	std::vector<std::string>& getDrawOrderDirect() {
		return drawOrder;
	}

	//オブジェクト名でオブジェクトを取得
	template<typename T>
	T& getObject(const std::string& name) {
		std::unordered_map<std::string, ObjectEntry>::iterator it = objects.find(name);
		if (it == objects.end()) {
			//nameに一致する名前のオブジェクトがない
			throw std::runtime_error("オブジェクトが見つかりません: " + name);
		}

		return static_cast<T&>(*it->second.object);
	}

	std::unordered_map<std::string, ObjectEntry>& getObjects() {
		return objects;
	}
};
