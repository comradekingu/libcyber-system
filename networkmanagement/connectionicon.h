/*
    Copyright 2013 Jan Grulich <jgrulich@redhat.com>
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLASMA_NM_CONNECTION_ICON_H
#define PLASMA_NM_CONNECTION_ICON_H

#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/ActiveConnection>
#include <NetworkManagerQt/VpnConnection>
#include <NetworkManagerQt/WirelessNetwork>
#if WITH_MODEMMANAGER_SUPPORT
#include <ModemManagerQt/modem.h>
#endif

class ConnectionIcon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connecting READ connecting NOTIFY connectingChanged)
    Q_PROPERTY(QString connectionIcon READ connectionIcon NOTIFY connectionIconChanged)
    Q_PROPERTY(QString connectionTooltipIcon READ connectionTooltipIcon NOTIFY connectionTooltipIconChanged)
    Q_PROPERTY(bool needsPortal READ needsPortal NOTIFY needsPortalChanged)
    Q_PROPERTY(QString currentSSID READ currentSSID NOTIFY currentSSIDChanged)

public:
    explicit ConnectionIcon(QObject* parent = nullptr);
    ~ConnectionIcon() override;

    bool connecting() const;
    QString connectionIcon() const;
    QString connectionTooltipIcon() const;

    QString currentSSID() const;

    bool needsPortal() const { return m_needsPortal; }

private Q_SLOTS:
    void activatingConnectionChanged(const QString & connection);
    void activeConnectionAdded(const QString & activeConnection);
    void activeConnectionDestroyed();
    void activeConnectionStateChanged(NetworkManager::ActiveConnection::State state);
    void carrierChanged(bool carrier);
    void connectivityChanged(NetworkManager::Connectivity connectivity);
    void deviceAdded(const QString & device);
    void deviceRemoved(const QString & device);
    void networkingEnabledChanged(bool enabled);
    void primaryConnectionChanged(const QString & connection);
#if WITH_MODEMMANAGER_SUPPORT
    void modemNetworkRemoved();
    void modemSignalChanged(const ModemManager::SignalQualityPair &signalQuality);
    void setIconForModem();
#endif
    void statusChanged(NetworkManager::Status status);
    void setWirelessIconForSignalStrength(int strength);
    void vpnConnectionStateChanged(NetworkManager::VpnConnection::State state, NetworkManager::VpnConnection::StateChangeReason reason);
    void wirelessEnabledChanged(bool enabled);
    void wirelessNetworkAppeared(const QString &network);
    void wwanEnabledChanged(bool enabled);
Q_SIGNALS:
    void connectingChanged(bool connecting);
    void connectionIconChanged(const QString & icon);
    void connectionTooltipIconChanged(const QString & icon);
    void needsPortalChanged(bool needsPortal);
    void currentSSIDChanged();

private:
    void addActiveConnection(const QString & activeConnection);
    void setConnecting(bool connecting);
    void setConnectionIcon(const QString & icon);
    void setConnectionTooltipIcon(const QString & icon);
    void setVpn(bool vpn);
    void setLimited(bool limited);
    uint m_signal;
    NetworkManager::WirelessNetwork::Ptr m_wirelessNetwork;

    QString m_currentSSID;

    bool m_connecting;
    bool m_limited;
    bool m_vpn;
    QString m_connectionIcon;
    QString m_connectionTooltipIcon;
    bool m_needsPortal = false;

    void setDisconnectedIcon();
    void setIcons();
    void setStates();
    void setWirelessIcon(const NetworkManager::Device::Ptr & device, const QString & ssid);
#if WITH_MODEMMANAGER_SUPPORT
    ModemManager::Modem::Ptr m_modemNetwork;
    void setModemIcon(const NetworkManager::Device::Ptr & device);
#endif
};

#endif // PLASMA_NM_CONNECTION_ICON_H
