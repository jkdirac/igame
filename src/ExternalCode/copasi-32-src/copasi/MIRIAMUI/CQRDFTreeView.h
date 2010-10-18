// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/MIRIAMUI/CQRDFTreeView.h,v $
//   $Revision: 1.2 $
//   $Name: Build-31 $
//   $Author: ssahle $
//   $Date: 2009/08/13 13:54:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQRDFTreeView_h
#define CQRDFTreeView_h

#include <map>
#include <qvariant.h>

#include "copasi/MIRIAMUI/ui_CQRDFTreeView.h"
#include "copasi/UI/copasiWidget.h"

class CRDFNode;
class CQRDFTreeViewItem;
class CRDFGraph;

class CQRDFTreeView : public CopasiWidget, public Ui::CQRDFTreeView
{
  Q_OBJECT

public:
  CQRDFTreeView(QWidget* parent = 0, const char* name = 0);
  virtual ~CQRDFTreeView();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

public slots:
  /**
   * Clear the listeview
   */
  virtual void clear();

  /**
   * Returns the list view item for node if it exists otherwise NULL.
   * @param const CRDFNode * pSubject
   * @return CQRDFTreeViewItem * listViewItem
   */
  CQRDFTreeViewItem * find(const CRDFNode * pNode);

  /**
   * Insert a map from a CRDFNode to a CRDFListView
   * @param const CRDFNode * pSubject
   * @param CQRDFTreeViewItem * pItem
   */
  void insert(const CRDFNode * pNode, CQRDFTreeViewItem * pItem);

  // Attributes
private:
  /**
   * A map to look up items associated with a node.
   */
  std::map< const CRDFNode *, CQRDFTreeViewItem * > mNode2Item;

  /**
   * The RDF Graph
   */
  CRDFGraph * mpGraph;

  void load();
};

#endif // CQRDFTreeView_h
