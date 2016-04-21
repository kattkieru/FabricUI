from FabricEngine import Core, FabricUI, Util, CAPI
from PySide import QtCore, QtGui
from FabricEngine.FabricUI import *
from FabricEngine.Util import *
from FabricEngine.CAPI import *
from SHAssetsMenu import SHAssetsMenu
from SHLightsMenu import SHLightsMenu
from SHContextualMenu import SHContextualMenu

class SHTreeView(SceneHub.SHBaseTreeView):
  selectionCleared = QtCore.Signal()
  itemSelected = QtCore.Signal(SceneHub.SHTreeItem)
  itemDeselected = QtCore.Signal(SceneHub.SHTreeItem)
  
  def __init__(self, client, scene):
    super(SHTreeView, self).__init__(client)
    self.shGLScene = scene
    self.setHeaderHidden(True)
    self.setSelectionMode(QtGui.QAbstractItemView.ExtendedSelection)
    self.setContextMenuPolicy(QtCore.Qt.CustomContextMenu)
    self.customContextMenuRequested.connect(self.onCustomContextMenu)
  
  def onCustomContextMenu(self, point):
    menu = SHContextualMenu(self.shGLScene, self)
    menu.exec_(self.mapToGlobal(point))
  
  def selectionChanged(self, selected, deselected):
    # clear selection (make sure 3D view is synchronized) if all elements are newly added
    clear = len(self.selectionModel().selectedIndexes()) == len(selected.indexes())

    super(SHTreeView, self).selectionChanged(selected, deselected)
    for index in deselected.indexes(): self.itemDeselected.emit(SceneHub.SHBaseTreeView.GetTreeItemAtIndex(index))
    if clear:
      self.selectionCleared.emit()
    for index in selected.indexes(): self.itemSelected.emit(SceneHub.SHBaseTreeView.GetTreeItemAtIndex(index))
 
  def mousePressEvent(self, event):
    if event.button() == QtCore.Qt.LeftButton:
      urlsList = []
      for index in self.selectedIndexes():
        url = self.shGLScene.getTreeItemPath(SceneHub.SHBaseTreeView.GetTreeItemAtIndex(index))
        if url != "none": 
          print "url " + str(url)
          urlsList.append(QtCore.QUrl(url))

      if len(urlsList) > 0:
        mimeData = QtCore.QMimeData()
        mimeData.setUrls(urlsList)
        # Create drag
        drag = QtGui.QDrag(self)
        drag.setMimeData(mimeData)
        drag.exec_(QtCore.Qt.CopyAction)

    super(SHTreeView, self).mousePressEvent(event)

  def mouseDoubleClickEvent(self, event):
    for index in self.selectedIndexes():
      item = SceneHub.SHBaseTreeView.GetTreeItemAtIndex(index)
      if item is not None:
        self.itemDoubleClicked.emit(item)   
