# zlistwidget
        QT控件，继承自QListWidget。本项目可以编译出插件，直接在QTCreator的Design中使用。
        主要的源码文件只有zlistwidget.h/zlistwidget.cpp，其它文件是插件项目文件。
```cpp
void MainWindow::on_button3_clicked()
{
    ZListWidget * w = new ZListWidget(this);
    w->setGeometry(QRect(100, 100, 200, 300));

    QString text;
    for (int i = 0; i < 5; i++) {
        text = QString("New Item %1").arg(i);
        QListWidgetItem * pItem =  new QListWidgetItem(text, w);
        QIcon icon;
        if (i == 0) {
            icon.addFile(":/images/images/flash.png", QSize(16, 16));
            icon.addFile(":/images/images/favorite.png", QSize(16, 16), QIcon::Selected, QIcon::Off);
            pItem->setIcon(icon);//QIcon(":/images/images/favorite.png"));
        }
        else if (i == 1) {
            pItem->setIcon(QIcon(":/images/images/flash.png"));
        }
        else if (i == 2) {
            pItem->setIcon(QIcon(":/images/images/history.png"));
        }
    }
    w->setItemHeight(40);
    w->show();
}
```
        界面截图如下：
        ![screenshot1](https://github.com/brucezhao/zlistwidget/blob/master/images/Screenshot1.png)

        下面是该控件在一个项目中的使用案例：
        ![screenshot2](https://github.com/brucezhao/zlistwidget/blob/master/images/Screenshot2.png)
