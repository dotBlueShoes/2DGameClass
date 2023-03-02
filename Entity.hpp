#pragma once
#include "Framework.hpp"

// Delete It later
#include "Components/Transform.hpp"

namespace Entity {

	using Component = any;
	using Components = Component*;

	using Entity = any;
	using Entities = Entity*;
	using EntitiesBuffor = Entities;

	//namespace Map {
	//	size currentOffset = 0;
	//}

	getter CreateEntitiesBuffor(const size& length) {
		return new Entity[length + 1];
	}

	template <class T>
	block CreateEntitiesCPY(
		/*out*/ EntitiesBuffor& buffor,
		const T& entity,
		const size& length,
		const size& offset = 0
	) {
		//Map::currentOffset += length;
		for (size i = 0; i < length; i++) {
			buffor[offset + i] = new T(entity);
		}
	}

	// ! REFERENCE SHOULD REFERENCE IN SOME COMPONENTS OTHER SHOULD BE LEFT.
	// ! FOR INSTANCE WE DON'T WANT TO SHARE POSITION OF SAME 100 OBJECTS.
	template <class T>
	block CreateEntitiesREF(
		/*out*/ EntitiesBuffor& buffor,
		T& entity,
		const size& length,
		const size& offset = 0
	) {
		for (size i = 0; i < length; i++) {
			buffor[offset + i] = &entity;
		}
	}

	// CreateEntitiesMOV

	// 2023-03-02 STARTS
	
	// - czy mo�na zdeklarowa� rozmiar bufora dla range'u dla komponentu przed ich utwprzeniem?
	// TABLICA RANGE�W MO�E BY� OKRE�LONA ROZMIAREM PRZED ! operujemy na ��cznej ilo�ci danego komponentu z pomoc� offset i size range'a.

	// - Jak tworzy� range'e
	// : z ifem
	// : bez if'a

	// #1
	// - 0->0 means: none, 
	// - 0->5 and entitiesCount = 5 means: change range to [ 0 -> 5 + count ],
	// - 0->5 and entitiesCount = 10 means: add range [ 10 -> count ]
	// : range.offset + range.size !> entitiesCount !!! To zgodnie z implementacj� nie powinno nigdy zaj��.

	//using ComponentsBuffor = Components;

	struct ComponentsBuffor {
		Components components;
		Ranges ranges;
		size rangesCount;
	};

	struct SampleEntityComponentREF {
		ComponentsBuffor* transforms;
		ComponentsBuffor* rigidBodys;
		ComponentsBuffor* surfaces;
	};

	template <class T>
	block CreateEntitiesCPYA(
		const T& entity,					// prefab like entity that will be copied onto components buffors
		const size& count,					// number of copies
		/*out*/ SampleEntityComponentREF& componentBuffors,
		// /*out*/ ComponentsBuffor& buffor1,	// component buffor [Transform]. + Information about ranges #1
		// /*out*/ ComponentsBuffor& buffor2,  // component buffor [RigidBody]
		// /*out*/ ComponentsBuffor& buffor3,  // component buffor [Surface]
		/*out*/ size& entitiesCount			// amount of all entities.
	) {

	}

	// This leads us to.
	// 1. FOREACH would perform per component buffor therefore there is no if statement other then the one in loop
	//  that goes through ranges.
	// 2. Each Coponent has it's own buffor and ranges - an array that has a size that has to be set.
	// 3. PROBLEM WITH component size and range 
	//  If we would have 3000 entities where 
	//   - first 30 have both Transform and Ridigbody
	//   - next 1485 only Transform
	//   - next 1485 have only Ridigbody
	//  Then the algorith would go thought 1st range sucesfully and then will be going though the rest counting every next offset and size till entityCount
	//   but knowing that a pair of these components can be found only in first 30 elements would fasten the algorithm.
	//   Therefore:
	//    a) an if statement that would check whether 
	//	  b) another method-system to operate on ranges of pairs of components that would become availible through sorting.
	//  Transform -> [00001111111111111111111]
	//  RigidBody -> [00002222222222222222222]

	// PYTANIE KO�COWE CZY SORTOWANIE MA ZNACZENIE
	//  bo to sortowanie jest istot� range'�w
	//  range'e s�u�� do zooptymalizowania przemieszczania si� po bufforach.

	// ##### 2023-03-02 ENDS 

	//block DeleteEntities(/*out*/ EntitiesBuffor& buffor, const size& length, const size& offset = 0) {
	//	for (size i = 0; i < length; i++) {
	//		delete buffor[offset + i];
	//	}
	//}

	block DeleteEntitiesBuffor(/*out*/ EntitiesBuffor& buffor) {
		//DeleteEntities(buffor, bufforLength);
		// TODO delete[][] ?
		delete[] buffor;
	}

	//block DeleteMainEntitiesBuffor(/*out*/ EntitiesBuffor& buffor, const size& bufforLength) {
	//	for (size i) {
	//
	//	}
	//}

	/*
	 * Links one buffor to another by making it's last member pointer to passed buffer.
	*/
	block Link(/*out*/ EntitiesBuffor& buffor, const size& bufforLength, EntitiesBuffor& other) {
		buffor[bufforLength] = other;
	}

	// Ranges specify the entities in entity lists that have required components.
	//  because components can be only added at creation.
	//  therefore thier position in buffors in known.

	struct Range {
		size offset, value;
	};

	using Ranges = Range*;

	//struct System {
	//	Entities entities;
	//	const Ranges ranges;
	//	const size rangesLength;
	//};

	

	// Example EntityBuffor
	//  1, 1, 1, 1, 1, link
	//  1, 1, 1, 1, 1, link
	//  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, link
	//  1, 2, 1, 2, 1, link
	//  2, 2, 2, 2, 1

	// Range - logika opisuj�ca rozmieszczenie szukanej grupy komponent�w w�r�d entities
	// Przyk�adowo chcemy znale�� same '1' bo te maj� transform, circleSurface i collision
	// Range sk�ada si� z 'offset' i 'size' - co m�wi przesu� si� o 'offset' i zczytaj kolejno 'size' element�w.

	// Ile istnieje kombinacji r�nych Range ?
	//  1. ka�dy pojedy�czy element
	//  2. ka�da para element�w
	//  3. ka�da grupa 3 element�w
	//  4. ka�da grupa n element�w ...

	// Je�li ka�dy komponent mia�by ID
	//  i je�li ich dodanie dawa�o unikaln� warto��
	//  to chc�c znale�� dan� grup� wystarczy�oby
	//  doda� warto�ci komponent�w grupy i 
	//  odejmowa� wyszukiwane od tej liczby 
	//  tylko �e IF == 0 b�dzie konieczny.

	// Shuffle
	// - Tylko dla pojedy�czego buffora.
	// ... je�li chcemy u�o�y� te� elementy w bufforach podrz�dnych to trzeba scali� buffory.

	// Docelowo chce przekaza� zwyk�� prost� pozycj� element�w.
	//  - aby da�o si� wskaza� 1, 2, 3 element
	//  - jak i powiedzie� tylko te z transform, circleSurface i collision
	//
	// Range
	//  - wska�e 1, 2, 3 element
	//  - ale mo�na go stworzy� zczytuj�c pewne informacje.
	//  : Jak znale�� b�d� i zachowa� informacje o komponentach ENTITY ?
	//   - 1. EntityIdentity - int reprezentuj�cy dany ENTITY obiekt nie instacj�, nie komponent.
	//   IF == 0 
	//   - 2. EntityIdentityMap - informacja o typie wszystkich dotychczasowo stworzonych Enitty
	//   {0000}{1111}{0000}{11}{22}{333333}{11} - przyk�ad mapy
	//	     {00000000000000}{11111111}{00}		- przyk�ad wynikowego Range
	// jak to: zapisywa�? zwi�ksza�? schuffle?
	//   

	template <class... Ts>
	//using System = T*; // functionPTR that takes T
	using System = void(*)(Ts...);

	template <class ... Ts>
	block ForEach(
		Entities entities,
		Ranges ranges,
		size rangesLength
	) {
	}

	template <class ... Ts>
	block ForEach(
		Entities entities,
		Ranges ranges,
		size rangesLength,
		System<Ts...> system
	) {
		//size offsetSum = 0;

		//(PlayerCircle*)entities[0]->moveData;
		// NIE MOG� WYCI�GN�� ZMIENNEJ NIE ZNAJ�C TYPU
		// Wyci�gni�ta lekcja...
		//  Zamiast operowa� na typach trzeba operowa� na bajtach.
		//  To oznacza �e musz� wskaza� gdzie w jakim obiekcjie Entity znajduje si� dany komponent.
		// https://www.youtube.com/watch?v=s6TMa33niJo

		{ // THAT WORKS !
			// czyli musz� zna� offset byte'�w wzgl�dem danego typu
			// czyli MUSZ� zna� kolejno�� TYP�W entity wewn�trz buffora bo pozycja komponentu wzgl�dem entity jest cholernie wa�na.
			// dlaczego wgl tworz� obiekt za obiektem zamiast 100 podobiekt�w 100 podobiekt�w 100 podobiekt�w?
			// ka�dy komponent mia�by wtedy swoj� tablic� Ranges
			auto&& entity = entities[0];
			Transform::Transform* transform = (Transform::Transform*)entity;

			std::cout << transform->position.x << transform->position.y << std::endl;
			std::cout << transform->rotation << std::endl;
			std::cout << transform->scale.x << transform->scale.y << std::endl;
		}

		//for (size i = 0; i < rangesLength; i++) {
		//	auto& range = ranges[i];
		//	for (size j = range.offset; j < range.offset + range.value; j++) {
		//	}
		//}

		//for (size i = 0; i < system.rangesLength; i++) {
		//	offsetSum += system.ranges[i].offset;
		//	for (size j = 0; j < system.ranges[i].value; j++) {
		//		auto entity = (T*)system.entities[offsetSum + j];
		//		// Callback ?
		//	}
		//	offsetSum += system.ranges[i].value;
		//}

	}



}