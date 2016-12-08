#include <QPen>
#include <QPainter>
#include <QDebug>
#include "zlistwidget.h"

//文字开始位置
const int C_TEXT_LEFT_MARGIN = 50;
//指示条宽度
const int C_INDICATOR_WIDTH = 5;

ZListWidget::ZListWidget(QWidget *parent, int paintType) :
    QListWidget(parent), m_paintType(paintType)
{
    this->setFrameShape(NoFrame);
    this->setSpacing(0);
    connect(this, &ZListWidget::itemSelectionChanged, this, &ZListWidget::onItemSelectionChanged);

    m_itemHeight = 35;

    m_color = QColor(198, 198, 198);
    m_backgroundColor = QColor(76, 83, 89);
    m_selectionColor = QColor(99, 176, 72);
    m_selectionBackgroundColor =  QColor(76, 83, 89);
    m_gridLineColor = QColor(87, 95, 103);
    this->setIconSize(QSize(16, 16));
}

int ZListWidget::itemHeight()
{
    return m_itemHeight;
}

void ZListWidget::setItemHeight(int height)
{
    m_itemHeight = height;

    QListWidgetItem * pItem = NULL;
    QSize size;
    for (int i = 0; i < this->count(); i++) {
        pItem = this->item(i);
        if (i == 0) {
            size = pItem->sizeHint();
            size.setHeight(m_itemHeight);
        }
        pItem->setSizeHint(size);
    }
}

const QColor &ZListWidget::color() const
{
    return m_color;
}

void ZListWidget::setColor(const QColor &color)
{
    if (color != m_color) {
        m_color = color;
        this->update();
    }
}

const QColor &ZListWidget::backgroundColor()
{
    return m_backgroundColor;
}

void ZListWidget::setBackgroundColor(const QColor &color)
{
    if (color != m_backgroundColor) {
        m_backgroundColor = color;
        this->update();
    }
}

const QColor &ZListWidget::gridLineColor() const
{
    return m_gridLineColor;
}

void ZListWidget::setGridLineColor(const QColor &color)
{
    if (color != m_gridLineColor) {
        m_gridLineColor = color;
        this->update();
    }
}

const QColor &ZListWidget::selectionColor() const
{
    return m_selectionColor;
}

void ZListWidget::setSelectionColor(const QColor &color)
{
    if (color != m_selectionColor) {
        m_selectionColor = color;
        this->update();
    }
}

const QColor &ZListWidget::selectionBackgroundColor() const
{
    return m_selectionBackgroundColor;
}

void ZListWidget::setSelectionBackgroundColor(const QColor &color)
{
    if (color != m_selectionBackgroundColor) {
        m_selectionBackgroundColor = color;
        this->update();
    }
}

void ZListWidget::showEvent(QShowEvent *event)
{
    if (this->count() > 0) {
        QListWidgetItem * pItem = this->item(0);
        if (pItem->sizeHint().height() != m_itemHeight) {
            setItemHeight(m_itemHeight);
        }
    }

    QListWidget::showEvent(event);
}


void ZListWidget::onItemSelectionChanged()
{
    //当spacing大于0时，如果不repaint，spacing区域不会更新，导致显示不正常
    if (this->spacing() > 0)
        this->viewport()->repaint();
}


void ZListWidget::paintEvent(QPaintEvent * event)
{
    if (m_paintType != 0) {
        QListWidget::paintEvent(event);
        return;
    }

    QPainter painter(this->viewport());
    QRect paintRect = this->rect();
    QListWidgetItem * pItem = NULL;
    QSize size(paintRect.width(), m_itemHeight);
    QPoint point;

    //绘制背景色
    painter.fillRect(paintRect.x(), paintRect.y(), paintRect.width(), paintRect.height(), m_backgroundColor);

    //设置图标区域
    int iconX = (C_TEXT_LEFT_MARGIN - this->iconSize().width() - C_INDICATOR_WIDTH) / 2 + C_INDICATOR_WIDTH;
    int iconY = 0;
    int iSpacing = this->spacing();
    int y = iSpacing;

    point.setX(C_TEXT_LEFT_MARGIN);

    //确定要显示的item范围
    int iFrom = this->indexAt(QPoint(paintRect.x() + iSpacing, paintRect.y() + iSpacing)).row();
    int iTo = this->indexAt(QPoint(paintRect.x() + iSpacing, paintRect.height() - iSpacing)).row();
    iTo = iTo == -1 ? this->count()-1 : iTo;
    iTo = iTo < iFrom ? iFrom : iTo;
    QFont font = this->font();

    for (int i = iFrom; i <= iTo ; i++) {
        pItem = this->item(i);
        //画背景
        if (pItem->isSelected()) {
            painter.fillRect(0, y, size.width(), size.height(), m_selectionBackgroundColor);
            painter.fillRect(0, y, C_INDICATOR_WIDTH, size.height(), m_selectionColor);
            painter.setPen(m_selectionColor);
            font.setBold(true);
        }
        else {
            painter.fillRect(0, y, size.width(), size.height(), m_backgroundColor);
            painter.setPen(m_color);
            font.setBold(false);
        }

        //画图标
        QIcon icon = pItem->icon();
        if (!icon.isNull()) {
            iconY = (m_itemHeight - this->iconSize().height()) / 2 + y;
            QRect iconRect(QPoint(iconX, iconY), this->iconSize());
            if (pItem->isSelected()) {
                icon.paint(&painter, iconRect, Qt::AlignCenter, QIcon::Selected, QIcon::Off);
            }
            else {
                icon.paint(&painter, iconRect);
            }
        }

        //写字
        point.setY(y);
        painter.setFont(font);
        QRect rectItem(point, size);
        painter.drawText(rectItem, Qt::AlignLeft | Qt::AlignVCenter, pItem->text(), NULL);

        //画分隔线
        if (i > 0) {
            painter.setPen(m_gridLineColor);
            painter.drawLine(0, y - this->spacing(), paintRect.width(), y - this->spacing());
        }

        y += size.height() + this->spacing() * 2;
    }

    painter.end();
}
