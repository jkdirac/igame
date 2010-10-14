/* Begin CVS Header
$Source: /fs/turing/cvs/copasi_dev/copasi/UI/ObjectBrowserItem.h,v $
$Revision: 1.47 $
$Name: Build-31 $
$Author: shoops $
$Date: 2009/02/19 19:53:30 $
End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description:
Date: 04/03
Comment : Copasi Object Browser including:

CBrowserObject: A complex structure uiniquely map to a CopasiObject
ObjectBrowserItem: A wraper to a CBrowserObject,
there may exist multiply wrappers to one CBrowserObject
ObjectListItem
ObjectList: A queue for all element:
The reason I dont use std:vector is
for efficiency requirement for all
object browser item update
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef OBJECT_BROWSER_ITEM_H
#define OBJECT_BROWSER_ITEM_H

#include "copasi.h"
#include "q3listview.h"

class Q3ListViewItem;
class Q3ListView;
class CCopasiObject;

/* Macro:
 define the status of Objects(items) in object browser
 */
#define NOCHECKED -1
#define ALLCHECKED 1
#define PARTCHECKED 0
/* Macro:
 define the number space for the key
   KEYBASE: represent the base address for key
 */
#define KEYBASE 0

/* Enumerate:
 define 3 types of objects/items in Object Browser
 */
enum objectType {FIELDATTR = 0, OBJECTATTR, CONTAINERATTR};

class ObjectList;

/* class CBrowserObject
 define the structure wrapper for a copasiObject
 */
class CBrowserObject
  {
  public:
    const CCopasiObject* pCopasiObject;
    bool mChecked;
    ObjectList* referenceList; //keep pointer to all its referenced items for later update
    CBrowserObject();
    ~CBrowserObject();
  };

/* class ObjectBrowserItem
 define the UI wrapper for a CBrowserObject
 */
class ObjectBrowserItem : public Q3ListViewItem
  {
  private:
    static long KeySpace;
    CBrowserObject* pBrowserObject;
    objectType mType;
    QString mKey;

  public:
    static void resetKeySpace()
    {
      KeySpace = KEYBASE;
    }

    static long getKeySpace()
    {
      return KeySpace;
    }

    CBrowserObject* getObject()
    {
      return pBrowserObject;
    }

    virtual QString key (int C_UNUSED(column), bool C_UNUSED(ascending)) const
      {
        return mKey;
      }

    ObjectBrowserItem (Q3ListView * parent = NULL, ObjectBrowserItem * after = NULL, const CCopasiObject* mObject = NULL, ObjectList* pList = NULL);
    ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after = NULL, const CCopasiObject* mObject = NULL, ObjectList* pList = NULL);
    virtual ~ObjectBrowserItem()
    {
      //      if (getType() != FIELDATTR) //To avoid cross reference/multi deletion
      pdelete(pBrowserObject);
    }

    void attachKey();

    void reverseChecked();
    bool isChecked() const;

    void setObjectType(objectType newType)
    {
      mType = newType;
    }

    void setBrowserObject(CBrowserObject* updateObject)
    {
      pBrowserObject = updateObject;
    }

    objectType getType()
    {
      return mType;
    }

    //-1 if this is no user checked
    //0 if this is only partly checked
    //1 if this is full checked
    int nUserChecked();
  };

typedef ObjectBrowserItem* pObjectBrowserItem;
/* class ObjectListItem
 define the status of Objects(items) in object browser
 */
struct ObjectListItem
  {
    ObjectListItem(ObjectBrowserItem* item, ObjectListItem* next, ObjectListItem* last)
    {
      pItem = item;
      pNext = next;
      pLast = last;
    }
    ObjectBrowserItem* pItem;
    ObjectListItem* pNext;
    ObjectListItem* pLast;
  };

class ObjectList
  {
  private:
    bool* quickIndex;
    ObjectBrowserItem **pointerList;
    int index_length;
    ObjectListItem* root;
    int length;

  public:
    ObjectList();
    ~ObjectList()
    {
      if (index_length != 0)
        {
          delete[] quickIndex;
          delete[] pointerList;
        }
      while (length > 0)
        pop();
    }
    void insert(ObjectBrowserItem* pItem); //insert at the first position
    ObjectListItem* getRoot();
    ObjectBrowserItem* pop();

  inline int len() {return length;};

    void sortList();
    void delDuplicate();
    bool sortListInsert(ObjectBrowserItem* pItem); //insert and keep the sort order

    void createBucketIndex(int max);
    void insertBucket(ObjectBrowserItem* pItem);
    ObjectBrowserItem* bucketPop(int& cursor);
    void destroyBucket();
  };

#endif
