//------------------------------------------------------------------------------
// 赵亦平 2016.12.08
// ZListWidget 1.0
// 继承自QListWidget，可以自定义item的高度，可以设置配色（无须通过QSS来实现)；
// 可以集成到QCreator中，在Design中使用；
//------------------------------------------------------------------------------
#ifndef ZLISTWIDGET_H
#define ZLISTWIDGET_H

#include <QListWidget>
#include <QPaintEvent>
#include <QRegion>

class ZListWidget : public QListWidget
{
    Q_OBJECT

    Q_PROPERTY(int itemHeight READ itemHeight WRITE setItemHeight)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor gridLineColor READ gridLineColor WRITE setGridLineColor)
    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor)
    Q_PROPERTY(QColor selectionBackgroundColor READ selectionBackgroundColor WRITE setSelectionBackgroundColor)
public:
    ZListWidget(QWidget *parent = 0, int paintType = 0);

    //设置每个item的高度
    int itemHeight();
    void setItemHeight(int height);
    //设置颜色
    const QColor & color() const;
    void setColor(const QColor & color);
    const QColor & backgroundColor();
    void setBackgroundColor(const QColor & color);
    const QColor & gridLineColor() const;
    void setGridLineColor(const QColor & color);
    const QColor & selectionColor() const;
    void setSelectionColor(const QColor & color);
    const QColor & selectionBackgroundColor() const;
    void setSelectionBackgroundColor(const QColor & color);
private:
    int m_paintType;
    int m_itemHeight;
    QColor m_color;
    QColor m_backgroundColor;
    QColor m_gridLineColor;
    QColor m_selectionColor;
    QColor m_selectionBackgroundColor;

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent * event);

    void onItemSelectionChanged();
};

#endif
