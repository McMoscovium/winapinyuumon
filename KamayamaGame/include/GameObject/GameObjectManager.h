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
	//���[�u�R���X�g���N�^
	GameObjectManager(GameObjectManager&& src) noexcept {
		if (this != &src) {
			objects = std::move(src.getObjects());
			drawOrder = src.getDrawOrderDirect();
		}
	}

	//�R�s�[������Z�q�i���L�����ړ��j
	GameObjectManager& operator=(GameObjectManager&& src)noexcept {
		if (this != &src) {
			objects = std::move(src.getObjects());
			drawOrder = src.getDrawOrderDirect();
		}
		return *this;
	}

	// �R�s�[�͋����Ȃ�
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;

	~GameObjectManager() = default;

	//�I�u�W�F�N�g����O�ɒǉ�
	template <typename T, typename... Args>
	T& addFront(const std::string& name, Args&&...args) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		if (objects.find(name) != objects.end()) {
			//���ł�name�Ɠ������O�̃I�u�W�F�N�g������
			throw std::runtime_error("�������O�̃I�u�W�F�N�g�����ɂ���܂�: " + name);
		}
		objects.emplace(name, ObjectEntry{ std::make_unique<T>(name, std::forward<Args>(args)...), std::type_index(typeid(T)) });
		drawOrder.push_back(name);
		return getObject<T>(name);
	}

	//�E�Ӓl�Q�Ƃ��󂯎���Ē��ڒǉ�
	template <typename T>
	T& addFrontDirect(const std::string& name, std::unique_ptr<T>&& object) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		if (objects.find(name) != objects.end()) {
			//���ł�name�Ɠ������O�̃I�u�W�F�N�g������
			throw std::runtime_error("�������O�̃I�u�W�F�N�g�����ɂ���܂�: " + name);
		}
		objects.emplace(name, ObjectEntry{ std::move(object),std::type_index(typeid(T)) });
		drawOrder.push_back(name);
		return getObject<T>(name);
	}
	
	//�`�揇�ɕ��ׂ�GameObject&�^�Q�Ƃ̃��X�g��Ԃ�
	std::vector<std::reference_wrapper<GameObject>> getDrawOrder()const {
		std::vector<std::reference_wrapper<GameObject>> result;
		for (const auto& name : drawOrder) {
			result.push_back(*objects.at(name).object);
		}
		return result;
	}

	//�`�揇�ɕ��ׂ����X�g�����̂܂ܕԂ�
	std::vector<std::string>& getDrawOrderDirect() {
		return drawOrder;
	}

	//�I�u�W�F�N�g���ŃI�u�W�F�N�g���擾
	template<typename T>
	T& getObject(const std::string& name) {
		std::unordered_map<std::string, ObjectEntry>::iterator it = objects.find(name);
		if (it == objects.end()) {
			//name�Ɉ�v���閼�O�̃I�u�W�F�N�g���Ȃ�
			throw std::runtime_error("�I�u�W�F�N�g��������܂���: " + name);
		}

		return static_cast<T&>(*it->second.object);
	}

	std::unordered_map<std::string, ObjectEntry>& getObjects() {
		return objects;
	}
};
