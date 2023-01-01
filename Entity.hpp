#pragma once
#include "Framework.hpp"

namespace Entity {

	using Component = any;
	using Entity = any;
	using Entities = Entity*;
	using EntitiesBuffor = Entities;

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
		for (size i = 0; i < length; i++) {
			buffor[offset + i] = new T(entity);
		}
	}

	// ! REFERENCE SHOULD REFERENCE IN SOME COMPONENTS OTHER SHOULD BE LEFT.
	// ! FOR INSTANCE WE DON'T WANT TO SHARE POSITION OF 100 SAME LOOKING OBJECTS.
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

	struct System {
		Entities entities;
		const Ranges ranges;
		const size rangesLength;
	};

	template <class T>
	block ForEach(System& system) {
		size offsetSum = 0;

		for (size i = 0; i < system.rangesLength; i++) {
			offsetSum += system.ranges[i].offset;
			for (size j = 0; j < system.ranges[i].value; j++) {
				auto entity = (T*)system.entities[offsetSum + j];
				// Callback ?
			}
			offsetSum += system.ranges[i].value;
		}

	}

}