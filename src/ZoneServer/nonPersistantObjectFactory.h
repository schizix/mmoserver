/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2008 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_NON_PERSISTANT_H
#define ANH_ZONESERVER_NON_PERSISTANT_H

#include "ZoneServer/TangibleObject.h"
#include "ZoneServer/StructureManager.h"
#include "DatabaseManager/DatabaseCallback.h"
#include <boost/pool/pool.hpp>
#include "FactoryBase.h"
#include "CampTerminal.h"

#define 	gNonPersistantObjectFactory	NonPersistantObjectFactory::getSingletonPtr()

class Item;
class Database;
class DataBinding;
class DispatchClient;
class ObjectFactoryCallback;


//=============================================================================


class NonPersistantObjectFactory : public FactoryBase
{
	public:

		static NonPersistantObjectFactory*	getSingletonPtr() { return mSingleton; }
		static NonPersistantObjectFactory*	Instance();

		static inline void deleteFactory(void)    
		{ 
			if (mSingleton)
			{
				delete mSingleton;
				mSingleton = 0;
			}
		}

		virtual void			handleDatabaseJobComplete(void* ref,DatabaseResult* result);

		virtual void			requestObject(ObjectFactoryCallback* ofCallback,uint64 id,uint16 subGroup,uint16 subType,DispatchClient* client);
		void					createTangible(ObjectFactoryCallback* ofCallback, uint32 familyId, uint32 typeId, uint64 parentId,Anh_Math::Vector3 position, string customName, DispatchClient* client);

		//spawns temporary objects for camps
		TangibleObject*			spawnTangible(StructureItemTemplate* placableTemplate, uint64 parentId, Anh_Math::Vector3 position, string customName, PlayerObject* player);
		CampTerminal*			spawnTerminal(StructureItemTemplate* placableTemplate, uint64 parentId, Anh_Math::Vector3 position, string customName, PlayerObject* player, StructureDeedLink*	deedData);

		void					_createItem(DatabaseResult* result,Item* item);

		uint64					getId(){return ++mId;}

	protected:
		NonPersistantObjectFactory(Database* database);
		~NonPersistantObjectFactory();

	private:

		// This constructor prevents the default constructor to be used, since it is private.
		NonPersistantObjectFactory();

		static NonPersistantObjectFactory*	mSingleton;

		void					_setupDatabindings();
		void					_destroyDatabindings();

		Database*				mDatabase;
		DataBinding*			mItemBinding;
		DataBinding*			mItemIdentifierBinding;
		uint64					mId;
};

//=============================================================================


#endif