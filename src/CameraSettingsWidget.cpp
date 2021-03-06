#include "CameraSettingsWidget.h"
#include "ui_CameraSettingsWidget.h"

#include "Device.h"
#include "SettingsProvider.h"

#define BOUNDING_BOX_KEY "bounding_box"
#define NUM_BLOB_LABELS_KEY "num_blob_labels"

CameraSettingsWidget::CameraSettingsWidget(Device* device, QWidget* const parent)
        : StandardWidget(device, parent)
        , ui(new Ui::CameraSettingsWidget)
{
        ui->setupUi(this);
        performStandardSetup(tr("Camera Settings Widget"));

        // Set current setting values
        const SettingsProvider* const settingsProvider = device->settingsProvider();
        if (settingsProvider) {
                const bool bbox = settingsProvider->value(BOUNDING_BOX_KEY, true).toBool();
                const int numLabels = settingsProvider->value(NUM_BLOB_LABELS_KEY, 0).toInt();

                ui->boundingBox->setChecked(bbox);
                ui->numLabels->setValue(numLabels);
        }
}

CameraSettingsWidget::~CameraSettingsWidget()
{
        SettingsProvider* const settingsProvider = device()->settingsProvider();
        if (settingsProvider) {
                settingsProvider->setValue(BOUNDING_BOX_KEY, ui->boundingBox->isChecked());
                settingsProvider->setValue(NUM_BLOB_LABELS_KEY, ui->numLabels->value());
                settingsProvider->sync();
        }

        delete ui;
}