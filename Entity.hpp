#pragma once
#include "Framework.hpp"

namespace Entity {

	using Component = any;
	using Entity = any;
	using Entities = Entity*;
	using EntitiesBuffor = Entities;

	getter CreateEntitiesBuffor(const size& length) {
		return new Entity[length];
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

	block DeleteEntities(/*out*/ EntitiesBuffor& buffor, const size& length, const size& offset = 0) {
		for (size i = 0; i < length; i++) {
			delete buffor[offset + i];
		}
	}

	block DeleteEntitiesBuffor(/*out*/ EntitiesBuffor& buffor, const size& bufforLength) {
		//DeleteEntities(buffor, bufforLength);
		// TODO delete[][] ?
		delete[] buffor;
	}

}