
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QProcess>
#include <QUrl>

class AppStore : public QWidget {
    Q_OBJECT

public:
    AppStore(QWidget *parent = nullptr) : QWidget(parent) {
        // Set up the main layout
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Create a list widget to display apps
        appList = new QListWidget(this);

        // Create a label for displaying app details
        appDetailsLabel = new QLabel("App Details:", this);

        // Create a line edit for manual app entry
        appEntryLineEdit = new QLineEdit(this);
        appEntryLineEdit->setPlaceholderText("Enter App Name");

        // Create a button to fetch and display apps
        QPushButton *fetchButton = new QPushButton("Fetch Apps", this);

        // Connect button click to fetchApps slot
        connect(fetchButton, &QPushButton::clicked, this, &AppStore::fetchApps);

        // Create a button to install the selected app
        installButton = new QPushButton("Install App", this);
        installButton->setEnabled(false);

        // Connect button click to installApp slot
        connect(installButton, &QPushButton::clicked, this, &AppStore::installApp);

        // Add widgets to the layout
        layout->addWidget(appList);
        layout->addWidget(appEntryLineEdit);
        layout->addWidget(fetchButton);
        layout->addWidget(appDetailsLabel);
        layout->addWidget(installButton);

        // Set up dark mode stylesheet
        setStyleSheet("background-color: #333; color: #fff;");

        // Set up the main window
        setLayout(layout);
        setWindowTitle("SpoinkStore");
    }

public slots:
    // Slot to handle fetching apps from Snap
    void fetchApps() {
        // Clear existing items
        appList->clear();

        // Run the snap find command to get available snaps
        QProcess process;
        process.start("snap", QStringList() << "find");

        // Wait for the process to finish
        process.waitForFinished();

        // Read the output of the process
        QString output = process.readAllStandardOutput();

        // Split the output into lines and add each line as an app
        QStringList lines = output.split('\n', Qt::SkipEmptyParts);
        appList->addItems(lines);

        // Enable the install button
        installButton->setEnabled(true);
    }

    // Slot to handle installing the selected app
    void installApp() {
        if (appList->currentItem()) {
            QString appName = appList->currentItem()->text();
            QMessageBox::information(this, "Installation", "Installing " + appName);

            // Run the snap install command to install the selected app
            QProcess process;
            process.startDetached("snap", QStringList() << "install" << appName);
        } else {
            QMessageBox::warning(this, "Installation", "Please fetch apps and select an app to install.");
        }
    }

    // Slot to fetch app details when a new app is selected
    void getAppDetails(QListWidgetItem *item) {
        QString appName = item->text();

        // Use the Snap Store API to get app details asynchronously
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, &AppStore::handleNetworkReply);

        QUrl apiUrl("https://api.snapcraft.io/v2/snaps/info/" + appName);
        QNetworkRequest request(apiUrl);

        manager->get(request);
    }

    // Slot to handle the network reply for app details
    void handleNetworkReply(QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            // Parse the JSON response
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();

            // Extract and display app details
            QString title = jsonObj["title"].toString();
            QString description = jsonObj["description"].toString();

            appDetailsLabel->setText("App Details:\nTitle: " + title + "\nDescription: " + description);
        } else {
            appDetailsLabel->setText("App Details: Error fetching app details");
        }

        reply->deleteLater();
    }

    // Slot to update the install button state based on app selection
    void updateInstallButtonState(QListWidgetItem *item) {
        installButton->setEnabled(item != nullptr);
    }

private:
    QListWidget *appList;
    QLabel *appDetailsLabel;
    QLineEdit *appEntryLineEdit;
    QPushButton *installButton;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AppStore myAppStore;
    myAppStore.show();

    return app.exec();
}

#include "main.moc"
