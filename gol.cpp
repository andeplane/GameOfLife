#include "gol.h"
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <cmath>

GOL::GOL(QQuickItem *parent) : QQuickPaintedItem(parent),
    m_size(0), m_isEmpty(true)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

int GOL::size() const
{
    return m_size;
}


void GOL::mousePressEvent(QMouseEvent *event)
{
    togglePoint(event->x(), event->y());
}


void GOL::mouseMoveEvent(QMouseEvent *event)
{
    if(event->x()>=width() || event->y()>=height()) {
        return;
    }

    togglePoint(event->x(), event->y());
}

void GOL::setSize(int size)
{
    if (m_size == size)
        return;

    m_size = size;
    emit sizeChanged(m_size);
    resize();
}

void GOL::setIsEmpty(bool isEmpty)
{
    if (m_isEmpty == isEmpty)
            return;

        m_isEmpty = isEmpty;
        emit isEmptyChanged(m_isEmpty);
}

void GOL::togglePoint(double x, double y)
{
    int column = m_size * x / width();
    int row = m_size * y / height();
    column = std::min(column, m_size-1);
    row = std::min(row, m_size-1);
    m_grid[column][row] = !m_grid[column][row];
    update();
}

void GOL::resize()
{
    m_grid.resize(m_size);
    m_oldGrid.resize(m_size);

    // Resize grid
    for(auto i=0; i<m_size; i++) {
        m_grid[i].resize(m_size);
        m_oldGrid[i].resize(m_size);
    }
}

bool GOL::newState(const QVector<QVector<bool> > &grid, int i, int j)
{
    int neighborSum = 0;
    for(int di=-1; di<=1; di++) {
        for(int dj=-1; dj<=1; dj++) {
            if(di==0&&dj==0) continue;

            int k = i+di;
            int l = j+dj;
            if(k<0 || k>= grid.size()) continue;
            if(l<0 || l>= grid[0].size()) continue;
            neighborSum += grid[k][l];
        }
    }

    if(grid[i][j]) {
        if(neighborSum<2) return false; // Alive, fewer than 2
        if(neighborSum<4) return true;  // Alive, 2 or 3
        return false; // Alive, more than 3
    } else {
        if(neighborSum==3) return true; // Dead, exactly 3
        return false; // Dead, not 3
    }
}

void GOL::step()
{
    m_oldGrid.swap(m_grid);
    for(auto i=0; i<m_size; i++) {
        for(auto j=0; j<m_size; j++) {
            m_grid[i][j] = newState(m_oldGrid, i, j);
        }
    }
    update();
}

void GOL::reset()
{
    for(auto i=0; i<m_size; i++) {
        for(auto j=0; j<m_size; j++) {
            m_grid[i][j] = 0;
        }
    }
    update();
}

bool GOL::isEmpty() const
{
    return m_isEmpty;
}

void GOL::paint(QPainter *painter)
{
    QImage image(m_size, m_size, QImage::Format_RGBA8888);
    QColor color = "white";
    bool hasLiveCells = false;
    for(auto i = 0; i < m_size; i++) {
        for(auto j = 0; j< m_size; j++) {
            image.setPixel(i, j, m_grid[i][j]*color.rgba());
            hasLiveCells |= m_grid[i][j];
        }
    }
    setIsEmpty(!hasLiveCells);

    painter->drawImage(boundingRect(), image);
}
