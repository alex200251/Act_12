#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Neurona::Neurona()
{
    id=0;
    voltaje=0;
    posicion_x=0;
    posicion_y=0;
    red=0;
    green=0;
    blue=0;
    sig=nullptr;
}


Neurona::Neurona(int id,float voltaje,int posicion_x,int posicion_y,int red,int green,int blue,Neurona *sig){
    this->id=id;
    this->voltaje=voltaje;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->red=red;
    this->blue=blue;
    this->green=green;
    this->sig=sig;
}
Grafo grafo;

void Admin::agregar_inicio(int id,float voltaje,int posicion_x,int posicion_y,int red,int green,int blue)
{
    Neurona *tmp=new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue,nullptr);
    grafo.agregarNodo(id, posicion_x, posicion_y);
    if(!h){
        h=tmp;
    }else{
        tmp->sig=h;
        h=tmp;
    }
}

void Admin::agregar_final(int id,float voltaje,int posicion_x,int posicion_y,int red,int green,int blue){
    Neurona *tmp=new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue,nullptr);
    grafo.agregarNodo(id, posicion_x, posicion_y);
    if(!h){
        h=tmp;
    }else{
        Neurona *aux = h;
        while (aux->sig != nullptr) {
            aux = aux->sig;
        }
        aux->sig = tmp;
    }
}

void Admin::mostrar(){
    Neurona *aux=h;
    if(h){
        while(aux){
            std::cout<<"Neurona: "<<aux->id<<std::endl;
            std::cout<<"Voltaje: "<<aux->voltaje<<std::endl;
            std::cout<<"posicion en X: "<<aux->posicion_x<<std::endl;
            std::cout<<"Posicion en Y: "<<aux->posicion_y<<std::endl;
            std::cout<<"Rojo: "<<aux->red<<std::endl;
            std::cout<<"Verde: "<<aux->green<<std::endl;
            std::cout<<"Azul: "<<aux->blue<<std::endl;
            aux=aux->sig;
        }
    }
    else{
        std::cout<<"Lista vacia!"<<std::endl;
    }

}

Admin *lis = new Admin();


int contador=0;
int id,posicion_x,posicion_y,red,green,blue,busc;
float voltaje;

void MainWindow::limpiarCampos() {
    id = 0;
    voltaje = 0.0;
    posicion_x = 0;
    posicion_y = 0;
    red = 0;
    green = 0;
    blue = 0;
    busc = 0;

    ui->insert_id->clear();
    ui->insert_voltaje->clear();
    ui->pos_x->setValue(0);
    ui->pos_y->setValue(0);
    ui->set_red->setValue(0);
    ui->set_green->setValue(0);
    ui->set_blue->setValue(0);
    ui->spinBox->setValue(0);
}

void MainWindow::on_insert_id_textChanged(const QString &arg1)
{
    std::string cadenaStd = arg1.toStdString();

    bool esNumeroValido = !cadenaStd.empty() && std::all_of(cadenaStd.begin(), cadenaStd.end(), [](char c) {
        return std::isdigit(static_cast<unsigned char>(c));
    });

    if (esNumeroValido)
    {
        id = std::stoi(cadenaStd);
    }
    else
    {
        id = 0;
    }
}

void MainWindow::on_insert_voltaje_textChanged(const QString &arg1)
{
    std::string cadenaStd = arg1.toStdString();

    try {
        voltaje = std::stof(cadenaStd);
    } catch (const std::invalid_argument& e) {
        voltaje = std::numeric_limits<float>::quiet_NaN();
    }
}

void MainWindow::on_pos_x_valueChanged(int value)
{
    posicion_x = value;
}

void MainWindow::on_pos_y_valueChanged(int value)
{
    posicion_y = value;
}

void MainWindow::on_set_red_valueChanged(int value)
{
    red = value;
}

void MainWindow::on_set_green_valueChanged(int value)
{
    green = value;
}

void MainWindow::on_set_blue_valueChanged(int value)
{
    blue = value;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    busc=arg1;
}



void MainWindow::on_buscarNeurona_clicked() {
    Neurona* neuronaEncontrada = lis->buscar(busc);

    if (neuronaEncontrada != nullptr) {

        int rowCount =ui->tableWidget->rowCount();
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->insertRow(rowCount);

        QTableWidgetItem* item;

        item = new QTableWidgetItem(QString::number(neuronaEncontrada->id));
        ui->tableWidget->setItem(rowCount, 0, item);

        item = new QTableWidgetItem(QString::number(neuronaEncontrada->voltaje));
        ui->tableWidget->setItem(rowCount, 1, item);

        item = new QTableWidgetItem(QString::number(neuronaEncontrada->posicion_x));
        ui->tableWidget->setItem(rowCount, 2, item);

        item = new QTableWidgetItem(QString::number(neuronaEncontrada->posicion_y));
        ui->tableWidget->setItem(rowCount, 3, item);

        item = new QTableWidgetItem(QString::number(neuronaEncontrada->red));
        ui->tableWidget->setItem(rowCount, 4, item);

        item = new QTableWidgetItem(QString::number(neuronaEncontrada->green));
        ui->tableWidget->setItem(rowCount, 5, item);

        item = new QTableWidgetItem(QString::number(neuronaEncontrada->blue));
        ui->tableWidget->setItem(rowCount, 6, item);
        QStringList headers;
        headers << "ID" << "Voltaje" << "Posición X" << "Posición Y" << "Rojo" << "Verde" << "Azul";
        ui->tableWidget->setHorizontalHeaderLabels(headers);



        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->resizeRowsToContents();
    } else {
        QMessageBox::warning(this, "Error", "Neurona no encontrada");
    }
}
void MainWindow::on_agregarInicio_clicked()
{
    lis->agregar_inicio(id,voltaje,posicion_x,posicion_y,red,green,blue);
    std::cout<<"Agregado"<<std::endl;
    contador++;
    limpiarCampos();
}


void MainWindow::on_AgregarFinal_clicked()
{
    lis->agregar_final(id,voltaje,posicion_x,posicion_y,red,green,blue);
    std::cout<<"Agregado"<<std::endl;
    contador++;
    limpiarCampos();

}

void MainWindow::on_mostrar_clicked()
{
    QString neuronasInfo;

    Neurona *aux = lis->h;
    if (aux) {
        while (aux)
        {
            QString neuronaStr = "Neurona: " + QString::number(aux->id) + "\n";
            neuronaStr += "Voltaje: " + QString::number(aux->voltaje) + "\n";
            neuronaStr += "Posicion en X: " + QString::number(aux->posicion_x) + "\n";
            neuronaStr += "Posicion en Y: " + QString::number(aux->posicion_y) + "\n";
            neuronaStr += "Rojo: " + QString::number(aux->red) + "\n";
            neuronaStr += "Verde: " + QString::number(aux->green) + "\n";
            neuronaStr += "Azul: " + QString::number(aux->blue) + "\n\n";

            // Agregar la información de la neurona a la cadena principal
            neuronasInfo += neuronaStr;

            aux = aux->sig;
        }
    }
    else
    {
        neuronasInfo = "Lista vacia!";
    }

    ui->plainTextEdit->setPlainText(neuronasInfo);
}



void MainWindow::on_Guardarlista_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Guardar archivo"), "/home", tr("Archivos de texto (*.txt)"));

    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (file.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);
            Neurona *aux = lis->h;
            while (aux)
            {
                out << aux->id << '|' << aux->voltaje << '|'
                    << aux->posicion_x << '|' << aux->posicion_y << '|'
                    << aux->red << '|' << aux->green << '|' << aux->blue << '\n';
                aux = aux->sig;
            }
            file.close();
            QMessageBox::information(this, "Éxito", "Lista de neuronas guardada en el archivo.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para escritura.");
        }
    }
}


void MainWindow::on_Leerlista_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Abrir archivo"), "/home", tr("Archivos de texto (*.txt)"));

    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&file);

            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList parts = line.split('|');
                if (parts.size() == 7)
                {
                    int id = parts[0].toInt();
                    float voltaje = parts[1].toFloat();
                    int posicion_x = parts[2].toInt();
                    int posicion_y = parts[3].toInt();
                    int red = parts[4].toInt();
                    int green = parts[5].toInt();
                    int blue = parts[6].toInt();
                    lis->agregar_final(id, voltaje, posicion_x, posicion_y, red, green, blue);
                    contador++;
                }
            }

            file.close();
            QMessageBox::information(this, "Éxito", "Lista de neuronas cargada desde el archivo.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para lectura.");
        }
    }
}

void MainWindow::on_Dibujar_clicked()
{
    // Limpiar la escena antes de dibujar
    scene->clear();

    // Dibujar nodos
    Neurona* aux = lis->h;
    while (aux != nullptr)
    {
        QColor color(aux->red, aux->green, aux->blue);
        QPen pen(color);
        QBrush brush(color);

        int x = aux->posicion_x;
        int y = aux->posicion_y;

        int width = aux->voltaje;
        int height = aux->voltaje;

        QGraphicsEllipseItem* neuronEllipse = scene->addEllipse(x, y, width, height, pen, brush);

        // Mostrar ID del nodo
        QGraphicsTextItem* textItem = scene->addText(QString::number(aux->id));
        textItem->setPos(x + width / 2 - 10, y + height / 2 - 10);

        aux = aux->sig;
    }


    ui->graphicsView->viewport()->update();
}

void Admin::ordenarId()
{
    Neurona *aux = h;
    Neurona *tmp = nullptr;
    if (!h)
    {
        QMessageBox msgBox;
        msgBox.setText("No existen neuronas");
        msgBox.exec();
        return;
    }

    bool band = true;
    int tid, tposx, tposy, tred, tgreen, tblue;
    float tvolt;

    while (band)
    {
        band= false;
        aux = h;

        while (aux->sig != tmp)
        {
            if (aux->id > aux->sig->id)
            {
                tid = aux->id;
                tvolt = aux->voltaje;
                tposx = aux->posicion_x;
                tposy = aux->posicion_y;
                tred = aux->red;
                tgreen = aux->green;
                tblue = aux->blue;

                aux->id = aux->sig->id;
                aux->voltaje = aux->sig->voltaje;
                aux->posicion_x = aux->sig->posicion_x;
                aux->posicion_y = aux->sig->posicion_y;
                aux->red = aux->sig->red;
                aux->green = aux->sig->green;
                aux->blue = aux->sig->blue;

                aux->sig->id = tid;
                aux->sig->voltaje = tvolt;
                aux->sig->posicion_x = tposx;
                aux->sig->posicion_y = tposy;
                aux->sig->red = tred;
                aux->sig->green = tgreen;
                aux->sig->blue = tblue;

                band = true;
            }
            aux = aux->sig;
        }
        tmp = aux;
    }
}




void Admin::ordenarVoltaje()
{
    if (!h)
    {
        QMessageBox msgBox;
        msgBox.setText("No existen neurona");
        msgBox.exec();
        return;
    }

    Neurona *aux = h;
    Neurona *tmp = nullptr;
    bool band = true;
    int tid, tposx, tposy, tred, tgreen, tblue;
    float tvolt;

    while (band)
    {
        band= false;
        aux = h;

        while (aux->sig != tmp)
        {
            if (aux->voltaje > aux->sig->voltaje)
            {
                tid = aux->id;
                tvolt = aux->voltaje;
                tposx = aux->posicion_x;
                tposy = aux->posicion_y;
                tred = aux->red;
                tgreen = aux->green;
                tblue = aux->blue;

                aux->id = aux->sig->id;
                aux->voltaje = aux->sig->voltaje;
                aux->posicion_x = aux->sig->posicion_x;
                aux->posicion_y = aux->sig->posicion_y;
                aux->red = aux->sig->red;
                aux->green = aux->sig->green;
                aux->blue = aux->sig->blue;

                aux->sig->id = tid;
                aux->sig->voltaje = tvolt;
                aux->sig->posicion_x = tposx;
                aux->sig->posicion_y = tposy;
                aux->sig->red = tred;
                aux->sig->green = tgreen;
                aux->sig->blue = tblue;

                band = true;
            }
            aux = aux->sig;
        }
        tmp = aux;
    }
}
void MainWindow::on_OrdID_clicked()
{
    lis->ordenarId();

    ui->plainTextEdit_2->clear();

    Neurona *aux = lis->h;
    while (aux) {
        QString neuronaInfo = "Neurona: " + QString::number(aux->id) + "\n";
        neuronaInfo += "Voltaje: " + QString::number(aux->voltaje) + "\n";
        neuronaInfo += "Posición en X: " + QString::number(aux->posicion_x) + "\n";
                       neuronaInfo += "Posición en Y: " + QString::number(aux->posicion_y) + "\n";
               neuronaInfo += "Rojo: " + QString::number(aux->red) + "\n";
        neuronaInfo += "Verde: " + QString::number(aux->green) + "\n";
        neuronaInfo += "Azul: " + QString::number(aux->blue) + "\n\n";

        ui->plainTextEdit_2->appendPlainText(neuronaInfo);

        aux = aux->sig;
    }
}

void MainWindow::on_OrdenarVolt_clicked()
{
    lis->ordenarVoltaje();

    ui->plainTextEdit_2->clear();

    Neurona *aux = lis->h;
    while (aux) {
        QString neuronaInfo = "Neurona: " + QString::number(aux->id) + "\n";
        neuronaInfo += "Voltaje: " + QString::number(aux->voltaje) + "\n";
        neuronaInfo += "Posición en X: " + QString::number(aux->posicion_x) + "\n";
                       neuronaInfo += "Posición en Y: " + QString::number(aux->posicion_y) + "\n";
               neuronaInfo += "Rojo: " + QString::number(aux->red) + "\n";
        neuronaInfo += "Verde: " + QString::number(aux->green) + "\n";
        neuronaInfo += "Azul: " + QString::number(aux->blue) + "\n\n";

        ui->plainTextEdit_2->appendPlainText(neuronaInfo);

        aux = aux->sig;
    }
}

void MainWindow::dibujarLineasFuerzaBruta() {
    QList<QGraphicsItem*> lineas = scene->items();

    // Limpiar la escena antes de dibujar
    for (QGraphicsItem* item : lineas) {
        if (item->type() == QGraphicsLineItem::Type) {
            scene->removeItem(item);
            delete item;
        }
    }

    if (lineasVisibles) {
        Neurona *aux = lis->h;
        while (aux != nullptr) {
            Neurona* neuronaMasCercana = nullptr;
            float distanciaMinima = std::numeric_limits<float>::max();

            Neurona* temp = lis->h;
            while (temp != nullptr) {
                if (aux != temp) {
                    float centro_x1 = aux->posicion_x + aux->voltaje / 2;
                    float centro_y1 = aux->posicion_y + aux->voltaje / 2;
                    float centro_x2 = temp->posicion_x + temp->voltaje / 2;
                    float centro_y2 = temp->posicion_y + temp->voltaje / 2;
                    float distancia = sqrt(pow(centro_x2 - centro_x1, 2) + pow(centro_y2 - centro_y1, 2));

                    if (distancia < distanciaMinima) {
                        distanciaMinima = distancia;
                        neuronaMasCercana = temp;
                    }
                }
                temp = temp->sig;
            }

            if (neuronaMasCercana != nullptr) {
                int idNodoInicio = aux->id;
                int idNodoFin = neuronaMasCercana->id;
                float peso = distanciaMinima;

                grafo.agregarArista(idNodoInicio, idNodoFin, peso);
                QPointF centroInicio(aux->posicion_x + aux->voltaje / 2, aux->posicion_y + aux->voltaje / 2);
                QPointF centroFin(neuronaMasCercana->posicion_x + neuronaMasCercana->voltaje / 2, neuronaMasCercana->posicion_y + neuronaMasCercana->voltaje / 2);

                scene->addLine(QLineF(centroInicio, centroFin));
            }
            aux = aux->sig;
        }
    }

    grafo.mostrarAristasEnEscena(scene);
    ui->graphicsView->viewport()->update();
}

void MainWindow::on_mostrarOcultarLineas_clicked() {
    lineasVisibles = !lineasVisibles;
    dibujarLineasFuerzaBruta();
}
void Grafo::agregarNodo(int id, float x, float y) {
    if (nodos.find(id) == nodos.end()) {
        Nodo nuevoNodo{ x, y };
        nodos[id] = nuevoNodo;
    } else {
        std::cout << "Error: Nodo con ID " << id << " ya existe en el grafo." << std::endl;
    }
}

void Grafo::agregarArista(int idNodoInicio, int idNodoFin, float peso) {
    if (nodos.find(idNodoInicio) != nodos.end() && nodos.find(idNodoFin) != nodos.end()) {
        aristas[idNodoInicio].emplace_back(idNodoFin, peso);
    } else {
        std::cout << "Error: Al menos uno de los nodos especificados no existe en el grafo." << std::endl;
    }
}

void Grafo::mostrarGrafo() {
    for (const auto& parNodo : nodos) {
        int idNodo = parNodo.first;
        const Nodo& nodo = parNodo.second;

        std::cout << "Nodo " << idNodo << ": (" << nodo.coordenada_x << ", " << nodo.coordenada_y << ")" << std::endl;

        if (aristas.find(idNodo) != aristas.end()) {
            std::cout << "   Aristas conectadas:" << std::endl;
            for (const auto& parArista : aristas[idNodo]) {
                int idNodoDestino = parArista.first;
                float pesoArista = parArista.second;

                std::cout << "      -> Nodo " << idNodoDestino << " (Peso: " << pesoArista << ")" << std::endl;
            }
        }
    }
}

void Grafo::mostrarAristasEnEscena(QGraphicsScene* scene) {
    for (const auto& parNodo : nodos) {
        int idNodo = parNodo.first;
        const Nodo& nodo = parNodo.second;

        if (aristas.find(idNodo) != aristas.end()) {
            for (const auto& parArista : aristas[idNodo]) {
                int idNodoDestino = parArista.first;
                float pesoArista = parArista.second;

                if (nodos.find(idNodoDestino) != nodos.end()) {
                    const Nodo& nodoDestino = nodos[idNodoDestino];

                    QPointF puntoInicio(nodo.coordenada_x, nodo.coordenada_y);
                    QPointF puntoFin(nodoDestino.coordenada_x, nodoDestino.coordenada_y);

                    // Crear una línea
                    QGraphicsLineItem* linea = scene->addLine(QLineF(puntoInicio, puntoFin));

                    // Crear un texto para mostrar la dirección y el peso
                    QGraphicsTextItem* texto = new QGraphicsTextItem;
                    texto->setPlainText(QString::number(idNodoDestino) + " (" + QString::number(pesoArista) + ")");
                    texto->setPos((puntoInicio + puntoFin) / 2);  // Coloca el texto en el centro de la línea
                    scene->addItem(texto);
                }
            }
        }
    }
}
