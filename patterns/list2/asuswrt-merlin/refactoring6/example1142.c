if ((sptr->version == SNMP_VERSION_3
#ifndef NETSNMP_DISABLE_SNMPV2C
                 || sptr->version == SNMP_VERSION_2c
#endif
                ) && minor == SNMPD_CALLBACK_SEND_TRAP2) {
                if (nptr->snmpNotifyType == SNMPNOTIFYTYPE_INFORM) {
                    template_pdu->command = SNMP_MSG_INFORM;
                } else {
                    template_pdu->command = SNMP_MSG_TRAP2;
                }
                send = 1;
            }