#ifndef GOL_H
#define GOL_H
#include <QQuickPaintedItem>

class GOL : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(bool isEmpty READ isEmpty WRITE setIsEmpty NOTIFY isEmptyChanged)
public:
    explicit GOL(QQuickItem *parent = nullptr);
    virtual void paint(QPainter *painter) override;
    int size() const;
    bool isEmpty() const;
    Q_INVOKABLE void step();
    Q_INVOKABLE void reset();


signals:
    void sizeChanged(int size);
    void isEmptyChanged(bool isEmpty);

public slots:
    void setSize(int size);
    void setIsEmpty(bool isEmpty);

private:
    QVector<QVector<bool>> m_grid;
    QVector<QVector<bool>> m_oldGrid;
    int m_size;
    bool m_isEmpty;
    bool newState(const QVector<QVector<bool>> &grid, int i, int j);
    void togglePoint(double x, double y);
    void resize();


protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // GOL_H
