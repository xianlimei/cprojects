#if LWIP_TCP_KEEPALIVE
if((u32_t)(tcp_ticks - pcb->tmr) >
         (pcb->keep_idle + (pcb->keep_cnt*pcb->keep_intvl))
         / TCP_SLOW_INTERVAL)
#else      
      if((u32_t)(tcp_ticks - pcb->tmr) >
         (pcb->keep_idle + TCP_MAXIDLE) / TCP_SLOW_INTERVAL)
#endif /* LWIP_TCP_KEEPALIVE */
      {
        LWIP_DEBUGF(TCP_DEBUG, ("tcp_slowtmr: KEEPALIVE timeout. Aborting connection to %"U16_F".%"U16_F".%"U16_F".%"U16_F".\n",
                                ip4_addr1_16(&pcb->remote_ip), ip4_addr2_16(&pcb->remote_ip),
                                ip4_addr3_16(&pcb->remote_ip), ip4_addr4_16(&pcb->remote_ip)));
        
        ++pcb_remove;
        ++pcb_reset;
      }
#if LWIP_TCP_KEEPALIVE
      else if((u32_t)(tcp_ticks - pcb->tmr) > 
              (pcb->keep_idle + pcb->keep_cnt_sent * pcb->keep_intvl)
              / TCP_SLOW_INTERVAL)
#else
      else if((u32_t)(tcp_ticks - pcb->tmr) > 
              (pcb->keep_idle + pcb->keep_cnt_sent * TCP_KEEPINTVL_DEFAULT) 
              / TCP_SLOW_INTERVAL)
#endif /* LWIP_TCP_KEEPALIVE */
      {
        tcp_keepalive(pcb);
        pcb->keep_cnt_sent++;
      }