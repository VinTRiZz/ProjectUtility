#include "dependencygraphwidget.h"
#include "ui_dependencygraphwidget.h"

#include <QDebug>

#include <QPainter>
#include <QPaintEngine>
#include <QMouseEvent>

#define BLOCK_HEIGHT 50
#define BLOCK_SPACE_SIZE 20

namespace GraphWidget
{

struct PaintTools
{
    QPainter * painter {nullptr};
    QBrush backgroundBrush; // Background color
    QBrush lineBrush;       // Defines color of lines and outlines
    QBrush appBrush;        // Defines color of app font
    QBrush libBrush;        // Defines color of lib font
    QBrush dependsBrush;

    QPen focusPen;  // To focus on lines
    QPen linesPen;  // For lines
    QPen objectPen; // For figure contures
    QPen textPen;    // For text write

    QFont appFont; // For text printing
    QFont libFont; // For text printing
    QFont depFont; // For text printing

    void setupPainter(QWidget * parent)
    {
        painter = new QPainter(parent);
        painter->setRenderHint(QPainter::Antialiasing);
    }

    void drawBackground(const QRect & rect)
    {
        // Fill background
        painter->setBrush(backgroundBrush);
        painter->drawRect(rect);
    }

    void setDefaultSettings()
    {
        linesPen = QPen(QColor(210, 200, 170), 3, Qt::PenStyle::DashLine, Qt::PenCapStyle::RoundCap); // 30, 60, 20 // Приятный цвет очень
        textPen = QPen(QColor(30, 30, 30), 2, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap);
        objectPen = QPen(QColor(20, 20, 20), 4, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap);
        focusPen = QPen(QColor(190, 50, 0), 3, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap);

        dependsBrush = QBrush(QColor(190, 180, 0));
        backgroundBrush = QBrush(QColor(62, 62, 62));

        appBrush = QBrush( QColor(115, 180, 115) );
        libBrush = QBrush( QColor(160, 160, 100) );

        appFont.setPixelSize(14);
        appFont.setBold(true);

        libFont.setPixelSize(12);

        depFont.setPixelSize(10);
        depFont.setBold(true);

        qDebug() << "[DependencyGraphWidget] Default settings set";
    }

    void setupForApp()
    {
        painter->setBrush(appBrush);
        painter->setFont(appFont);
        painter->setPen(objectPen);
    }

    void setupForLib()
    {
        painter->setBrush(libBrush);
        painter->setFont(libFont);
        painter->setPen(objectPen);
    }

    void setupForDepLine()
    {
        painter->setPen(linesPen);
    }

    void setFocused()
    {
        painter->setPen(focusPen);
    }

    void drawText(const QRect & pos, const QString & text)
    {
        painter->setPen(textPen);
        painter->drawText(pos, Qt::AlignCenter, text);
    }

    void drawDependCount(QRect pos, const int dependCount)
    {
        QString dependCountStr = QString::number(dependCount);

        const int newWidth = dependCountStr.length() * painter->font().pixelSize() + 3;

        pos.moveTo(pos.right() - newWidth + 2, pos.bottom() - newWidth + 2);
        pos.setWidth(newWidth);
        pos.setHeight(newWidth);

        painter->setPen(focusPen);
        painter->setBrush(dependsBrush);
        painter->drawRect(pos);

        painter->setPen(textPen);
        painter->setFont(depFont);
        painter->drawText(pos, Qt::AlignCenter, dependCountStr);
    }
};

}

using namespace GraphWidget;

struct DependencyGraphWidget::Impl
{
    bool areDependsUpdating {false};

    PaintTools m_paintTools;

    QVector<DependencyStruct *> allNodes;

    QVector<DependencyStruct *> nodeHistory;
    DependencyStruct * currentHead {nullptr};

    QStringList dependQuery;
    DependencyStruct * checkForRecurse(DependencyStruct * pParent)
    {
        bool recurseExist = false;
        for (DependencyStruct * dep : pParent->dependsFrom)
        {
            recurseExist = dependQuery.contains(dep->name);
            dependQuery << dep->name;

            if (recurseExist)
                return dep;

            if (checkForRecurse(dep))
                return dep;

            dependQuery.pop_back();
        }
        return nullptr;
    }

//    void setupTestDepends()
//    {
//        DependencyStruct * pMainNode {nullptr};
//        DependencyStruct * pHead {nullptr};
//        DependencyStruct * pChild {nullptr};
//        DependencyStruct * pChildChild {nullptr};

//        pMainNode = createNode("Приложение");
//        pMainNode->isApp = true;
//        pMainNode->position = QRect(100, 100, 100, 100);

//        QString nameBuffer;
//        for (int i = 1; i < 4; i++)
//        {
//            pHead = createNode(QString("Либа %1").arg(i));
//            pMainNode->dependsFrom.push_back(pHead);

//            for (int j = 5; j < 14; j++)
//            {
//                nameBuffer = QString("Либа %1").arg(j);

//                pChild = getNode(nameBuffer);
//                if (!pChild)
//                    pChild = createNode(nameBuffer);

//                if (!pHead->dependsFrom.contains(pChild))
//                    pHead->dependsFrom.push_back(pChild);

//                for (int k = 15; k < 20; k++)
//                {
//                    nameBuffer = QString("Либа %1").arg(k);

//                    pChildChild = getNode(nameBuffer);
//                    if (!pChildChild)
//                        pChildChild = createNode(nameBuffer);

//                    if (!pChild->dependsFrom.contains(pChildChild))
//                        pChild->dependsFrom.push_back(pChildChild);
//                }
//            }
//        }
//        currentHead = pMainNode;

//        qDebug() << "[\033[33mTEST\033[0m] Setup complete";
//    }

    DependencyStruct * getNode(const QString & name)
    {
        DependencyStruct * pFoundNode = nullptr;
        for (DependencyStruct * pNode : allNodes)
        {
            if (pNode->name == name)
            {
                pFoundNode = pNode;
                break;
            }
        }
        return pFoundNode;
    }

    DependencyStruct * createNode(const QString & name)
    {
        DependencyStruct * pNode = new DependencyStruct;
        pNode->name = name;
        allNodes.push_back(pNode);
        return pNode;
    }

    void removeNode(DependencyStruct * pNode)
    {
        for (auto node : allNodes)
        {
            if (node == pNode)
            {
                delete node;
                return;
            }
        }
    }

    void clear()
    {
        while (areDependsUpdating);
        areDependsUpdating = true;

        currentHead = nullptr;
        for (auto node : allNodes)
            delete node;
        allNodes.clear();
        nodeHistory.clear();

        areDependsUpdating = false;
    }
};

DependencyGraphWidget::DependencyGraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DependencyGraphWidget),
    m_pImpl {new Impl}
{
    ui->setupUi(this);

    m_pImpl->m_paintTools.setDefaultSettings();

    // m_pImpl->setupTestDepends();
}

DependencyGraphWidget::~DependencyGraphWidget()
{
    m_pImpl->clear();
    delete ui;
}

void DependencyGraphWidget::setHead(const QString &headName)
{
    while (m_pImpl->areDependsUpdating);
    m_pImpl->areDependsUpdating = true;

    m_pImpl->currentHead = m_pImpl->getNode(headName);

    m_pImpl->nodeHistory.clear();

    m_pImpl->areDependsUpdating = false;
    update();
}

void DependencyGraphWidget::setDependsVector(const QVector<DependencyStruct *> & depsVector)
{
    m_pImpl->clear();
    m_pImpl->areDependsUpdating = true;
    m_pImpl->allNodes = depsVector;
    m_pImpl->areDependsUpdating = false;
    update();
}

void DependencyGraphWidget::setDefaultSettings()
{
    while (m_pImpl->areDependsUpdating);
    m_pImpl->areDependsUpdating = true;
    m_pImpl->m_paintTools.setDefaultSettings();
    m_pImpl->areDependsUpdating = false;
    update();
}

void DependencyGraphWidget::clear()
{
    m_pImpl->clear();
    update();
}

void DependencyGraphWidget::drawObject(const DependencyStruct * object)
{
    if (object->isApp)
        m_pImpl->m_paintTools.setupForApp();
    else
        m_pImpl->m_paintTools.setupForLib();

    m_pImpl->m_paintTools.painter->drawRoundedRect(object->position, 10, 10);
    m_pImpl->m_paintTools.drawText(object->position, object->name);

    m_pImpl->m_paintTools.drawDependCount(object->position, object->dependsFrom.size());
}

void DependencyGraphWidget::connectDepends(DependencyStruct * head)
{
    m_pImpl->m_paintTools.setupForDepLine();

    for (DependencyStruct * pNode : head->dependsFrom)
        m_pImpl->m_paintTools.painter->drawLine(head->centerUp(), pNode->centerDown());
}

void DependencyGraphWidget::drawHistory()
{
    if (!m_pImpl->nodeHistory.size())
        return;

    int currentY = rect().height() - BLOCK_HEIGHT - BLOCK_SPACE_SIZE;
    DependencyStruct * pBufferNode {nullptr};
    for (DependencyStruct * pNode : m_pImpl->nodeHistory)
    {
        pNode->position.moveTo(rect().center().x() - pNode->position.width() / 2, currentY);
        drawObject(pNode);

        if (pBufferNode)
        {
            m_pImpl->m_paintTools.setupForDepLine();
            m_pImpl->m_paintTools.painter->drawLine(pBufferNode->centerUp(), pNode->centerDown());
        }
        pBufferNode = pNode;

        currentY -= BLOCK_HEIGHT + BLOCK_SPACE_SIZE;
    }

    m_pImpl->m_paintTools.setupForDepLine();
    m_pImpl->m_paintTools.painter->drawLine(pBufferNode->centerUp(), m_pImpl->currentHead->centerDown());
}

void DependencyGraphWidget::drawGraph(DependencyStruct * head)
{
    drawObject(m_pImpl->currentHead);

    int squareLength = 50, currentXPosLeft = head->centerUp().x() - head->dependsFrom.size() * squareLength;

    const int
            LINE_HEIGHT = 15,
            DEPENDS_OBJECT_HEIGHT = 30,
            DEPENDS_SPACE_SIZE = 35,
            DEPENDS_OBJECT_Y = head->position.top() - (LINE_HEIGHT + 2 * DEPENDS_OBJECT_HEIGHT)
    ;

    for (DependencyStruct * pNode : head->dependsFrom)
    {
        squareLength = pNode->name.length() * m_pImpl->m_paintTools.painter->font().pixelSize();

        pNode->position = QRect(currentXPosLeft, DEPENDS_OBJECT_Y, squareLength, DEPENDS_OBJECT_HEIGHT);

        drawObject(pNode);

        currentXPosLeft += squareLength + DEPENDS_SPACE_SIZE;
    }

    connectDepends(head);
}

void DependencyGraphWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    while (m_pImpl->areDependsUpdating);

    if (!m_pImpl->m_paintTools.painter)
        m_pImpl->m_paintTools.setupPainter(this);

    if (!m_pImpl->m_paintTools.painter->isActive())
        m_pImpl->m_paintTools.painter->begin(this);

    // Draw depends
    if (m_pImpl->allNodes.size() && m_pImpl->currentHead)
    {
        if (!m_pImpl->checkForRecurse(m_pImpl->currentHead))
        {
            m_pImpl->m_paintTools.drawBackground(rect());

            setMinimumWidth(m_pImpl->currentHead->dependsFrom.size() * 150);
            setMinimumHeight((m_pImpl->nodeHistory.size() + 2) * (BLOCK_HEIGHT + BLOCK_SPACE_SIZE));

            const int HEAD_WIDTH = m_pImpl->currentHead->name.length() * m_pImpl->m_paintTools.appFont.pixelSize();

            m_pImpl->currentHead->position = QRect(rect().center().x() - HEAD_WIDTH / 2, rect().height() - (m_pImpl->nodeHistory.size() + 1) * (BLOCK_HEIGHT + BLOCK_SPACE_SIZE), HEAD_WIDTH, BLOCK_HEIGHT);

            drawGraph(m_pImpl->currentHead);
            drawHistory();
        }
    }

    if (m_pImpl->m_paintTools.painter->isActive())
        m_pImpl->m_paintTools.painter->end();
}

void DependencyGraphWidget::mousePressEvent(QMouseEvent *e)
{
    if (!m_pImpl->currentHead)
        return;

    QPoint clickPos = e->pos();

    for (DependencyStruct * pNode : m_pImpl->allNodes)
    {
        if (pNode->position.contains(clickPos))
        {
            int nodeIndex = m_pImpl->currentHead->dependsFrom.indexOf(pNode);

            if (nodeIndex > -1)
            {
                for (DependencyStruct * depNode : m_pImpl->currentHead->dependsFrom)
                    depNode->position = QRect();
                m_pImpl->nodeHistory.push_back(m_pImpl->currentHead);
                m_pImpl->currentHead = pNode;

                qDebug() << "[DependencyGraphWidget] Switched to node:" << m_pImpl->currentHead->name;
            }
            else
            {
                nodeIndex = m_pImpl->nodeHistory.indexOf(pNode);

                if (nodeIndex != -1)
                {
                    m_pImpl->currentHead = pNode;
                    m_pImpl->nodeHistory.remove(nodeIndex, m_pImpl->nodeHistory.size() - nodeIndex);
                }

                qDebug() << "[DependencyGraphWidget] Returned to node:" << m_pImpl->currentHead->name;
            }
            update();

            emit updated();
            return;
        }
    }
}

