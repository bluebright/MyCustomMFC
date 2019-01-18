#pragma once

#ifndef _K_TREE_CTRL_H_
#define _K_TREE_CTRL_H_

#include <SDKDDKVer.h>
#include <afxcmn.h>


template<class lParamData>
class KTreeCtrl : public CTreeCtrl {

public:
	int GetItemOrderFromParent(HTREEITEM* childItem);
	BOOL GetChildItemFromParent(HTREEITEM* parentItem, HTREEITEM* resultChildItem, int targetIndex);
	//int GetChildItemDataFromParent(HTREEITEM* parentItem, HTREEITEM* resultChildItem, lParamData* data);
	BOOL GetChildItemDataFromParent(HTREEITEM* parentItem, lParamData& data, int targetIndex);
	BOOL GetChildItemDataFromParent_P(HTREEITEM* parentItem, lParamData** data, int targetIndex);
	HTREEITEM FindItem(HTREEITEM hRroot, const CString& name);

protected:

	afx_msg void OnTvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:

};


BEGIN_TEMPLATE_MESSAGE_MAP(KTreeCtrl, lParamData, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, &KTreeCtrl::OnTvnDeleteitem)
	//ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, Function!!!!!)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, &KTreeCtrl::OnTvnEndlabeledit)
END_MESSAGE_MAP()


/**
*
* Safe delete item when tree contain custom data in LPARAM
* (Prevent memory leak)
*
* @see http://mydevnote.tistory.com/242
*/
template<class lParamData>
void KTreeCtrl<lParamData>::OnTvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW> (pNMHDR);
	if (pNMTreeView == NULL)
		return;

	HTREEITEM hItem = pNMTreeView->itemOld.hItem;
	if (hItem == NULL)
		return;

	lParamData* p_my_data = (lParamData *)GetItemData(hItem);
	if (p_my_data != NULL) {
		delete(p_my_data);
		p_my_data = NULL;
	}

	*pResult = 0;
}


/**
* Need to enable "Edit Labels" Dialog properties
*
* @see https://docs.microsoft.com/en-us/windows/desktop/controls/tvn-endlabeledit
*/
template<class lParamData>
void KTreeCtrl<lParamData>::OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Pointer to an NMTVDISPINFO structure.
	//The item member of this structure is a TVITEM structure
	//whose hItem, lParam, and pszText members contain valid information about the item
	//that was edited. 
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	if (pTVDispInfo == NULL)
		return;

	TVITEM targetItem = pTVDispInfo->item;

	// If label editing was canceled, the pszText member of the TVITEM structure is NULL
	// otherwise, pszText is the address of the edited text.
	LPWSTR p_treeText = targetItem.pszText;

	if (p_treeText == NULL)
		return;
		
	//Apply edited text at tree control
	SetItemText(targetItem.hItem, p_treeText);

	//UpdateData(FALSE);
	*pResult = 0;
}

/**
* Get target item order from parent item
*/
template<class lParamData>
int KTreeCtrl<lParamData>::GetItemOrderFromParent(HTREEITEM* childItem) {

	if (childItem == NULL || *childItem == NULL)
		return -1;

	HTREEITEM targetItem = *childItem;
	HTREEITEM parentItem = GetParentItem(targetItem);

	if (parentItem == NULL)
		return -1;

	int childIndex = 0;
	HTREEITEM anotherChild = GetChildItem(parentItem);

	while (anotherChild) {
		if (anotherChild == targetItem)
			break;
		else {
			anotherChild = GetNextItem(anotherChild, TVGN_NEXT);
			++childIndex;
		}
	}

	return childIndex;
}

template<class lParamData>
BOOL KTreeCtrl<lParamData>::GetChildItemFromParent(HTREEITEM* parentItem, HTREEITEM* resultChildItem, int targetIndex) {

	if (parentItem == NULL || *parentItem == NULL)
		return FALSE;

	*resultChildItem = NULL;

	HTREEITEM m_parentItem = *parentItem;

	BOOL isChildContain = ItemHasChildren(m_parentItem);
	if (isChildContain) {

		int itemOrder = 0;
		HTREEITEM childItem = GetChildItem(m_parentItem);

		while (isChildContain) {
			if (itemOrder > targetIndex || childItem == NULL) {
				isChildContain = FALSE;
				break;
			}
			else if (itemOrder < targetIndex) {
				childItem = GetNextSiblingItem(childItem);
				itemOrder++;
			}
			else {
				//itemOrder == targetIndex
				*resultChildItem = childItem;
				break;
			}
		}
	}

	return isChildContain;
}

/**
* Use "GetChildItemFromParent" function
*/
template<class lParamData>
BOOL KTreeCtrl<lParamData>::GetChildItemDataFromParent(HTREEITEM* parentItem, lParamData& resultData, int targetIndex)
{
	HTREEITEM child = NULL;

	if (GetChildItemFromParent(parentItem, &child, targetIndex)) {		
		/*
		lParamData *lparamData = (lParamData *)GetItemData(child);
		resultData = *lparamData;
		return TRUE;
		*/
		
		DWORD_PTR dwordPtr = GetItemData(child);
		if (dwordPtr != NULL)
		{
			lParamData *lparamData = (lParamData *)dwordPtr;
			resultData = *lparamData;
			return TRUE;
		}
	}

	resultData = NULL;
	return FALSE;

}

/**
* Use "GetChildItemFromParent" function
*/
template<class lParamData>
BOOL KTreeCtrl<lParamData>::GetChildItemDataFromParent_P(HTREEITEM* parentItem, lParamData** resultData, int targetIndex)
{
	HTREEITEM child = NULL;

	if (GetChildItemFromParent(parentItem, &child, targetIndex)) {
		/*	lParamData *lparamData = (lParamData *)GetItemData(child);
			*resultData = lparamData;
			return TRUE;*/

		DWORD_PTR dwordPtr = GetItemData(child);
		if (dwordPtr != NULL)
		{
			lParamData *lparamData = (lParamData *)dwordPtr;
			*resultData = lparamData;
			return TRUE;
		}

	}
	*resultData = NULL;
	return FALSE;

}

template<class lParamData>
HTREEITEM KTreeCtrl<lParamData>::FindItem(HTREEITEM hRoot, const CString& name)
{
	while (hRoot != NULL)
	{
		CString text = GetItemText(hRoot);
		if (text.Compare(name) == 0)
			return hRoot;

		//HTREEITEM hItem = GetChildItem(hRoot);
		HTREEITEM hFound = FindItem(GetChildItem(hRoot), name);
		if (hFound)
			return hFound;

		hRoot = GetNextSiblingItem(hRoot);
	}

	return NULL;
}

#endif // !_K_TREE_CTRL_H_