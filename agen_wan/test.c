cJSON *name = cJSON_GetObjectItem(json_input, "name");

if (name != NULL && cJSON_IsString(name))
{
    snprintf(output->name, sizeof(output->name), "%s", name->valuestring);
}
else
{
    log_error("Key 'name' not found or not a string");
    return ERROR_INVALID_NAME;
}

cJSON *protocol = cJSON_GetObjectItem(json_input, "protocol");
if (protocol != NULL && cJSON_IsString(protocol))
{
    for (int i = 0; i < PROTO_SIZE; i++)
    {
        if (strcmp(protocol->valuestring, valid_protocol_type[i]) == 0)
        {
            output->protocol = (wan_protocol_t)i;
            break;
        }
    }
    if (output->protocol >= PROTO_SIZE)
    {
        log_error("Invalid protocol field in JSON");
        return ERROR_INVALID_PROTOCOL_TYPE;
    }
}
else
{
    log_error("Key 'protocol' not found");
    return ERROR_INVALID_JSON;
}

cJSON *gateway_type = cJSON_GetObjectItem(json_input, "gateway_type");
if (gateway_type != NULL && cJSON_IsNumber(gateway_type))
{
    for (int i = 0; i < GW_SIZE; i++)
    {
        if (strcmp(gateway_type->valuestring, valid_gateway_type[i]) == 0)
        {
            output->gateway_type = (wan_gateway_t)i;
            break;
        }
    }
    if (output->gateway_type >= GW_SIZE)
    {
        log_error("Invalid gateway_type field in JSON");
        return ERROR_INVALID_GATEWAY_TYPE;
    }
}
else
{
    log_error("Key 'gateway_type' not found");
    return ERROR_INVALID_GW;
}

cJSON *link_mode = cJSON_GetObjectItem(json_input, "link_mode");
if (link_mode != NULL && cJSON_IsNumber(link_mode))
{
    for (int i = 0; i < LINK_SIZE; i++)
    {
        if (strcmp(link_mode->valuestring, valid_link_mode[i]) == 0)
        {
            output->link_mode = (wan_linkmode_t)i;
            break;
        }
    }
    if (output->link_mode >= LINK_SIZE)
    {
        log_error("Invalid link_mode field in JSON");
        return ERROR_INVALID_LINK_MODE;
    }
}
else
{
    log_error("Key 'link_mode' not found");
    return ERROR_INVALID_JSON;
}
cJSON *mtu = cJSON_GetObjectItem(json_input, "mtu");
if (mtu != NULL && cJSON_IsNumber(mtu))
{
    output->mtu = (uint16_t)mtu->valueint;
}
else
{
    log_error("Invalid mtu field in JSON");
    return ERROR_INVALID_MTU;
}
cJSON *nat_enable = cJSON_GetObjectItem(json_input, "nat_enable");
if (nat_enable != NULL && cJSON_IsBool(nat_enable))
{
    output->nat_enable = (uint8_t)nat_enable->valueint;
}
else
{
    log_error("Invalid nat_enable field in JSON");
    return ERROR_INVALID_NAT;
}
cJSON *vlan = cJSON_GetObjectItem(json_input, "vlan");
if (vlan != NULL && cJSON_IsObject(vlan))
{
    cJSON *vlan_type = cJSON_GetObjectItem(vlan, "type");
    if (vlan_type != NULL && cJSON_IsString(vlan_type))
    {
        for (int i = 0; i < VLAN_SIZE; i++)
        {
            if (strcmp(vlan_type->valuestring, valid_vlan_type[i]) == 0)
            {
                output->vlan.type = (wan_vlan_type_t)i;
                break;
            }
        }
        if (output->vlan.type >= VLAN_SIZE)
        {
            log_error("Invalid vlan type field in JSON");
            return ERROR_INVALID_VLAN;
        }
    }
    else
    {
        log_error("Key 'type' not found in vlan");
        return ERROR_INVALID_JSON;
    }

    cJSON *vlan_id = cJSON_GetObjectItem(vlan, "id");
    if (vlan_id != NULL && cJSON_IsNumber(vlan_id))
    {
        output->vlan.id = (uint16_t)vlan_id->valueint;
    }
    else
    {
        log_error("Key 'id' not found in vlan");
        return ERROR_INVALID_JSON;
    }
}
else
{
    log_error("Key 'vlan' not found or not an object");
    return ERROR_INVALID_JSON;
}
cJSON *pppoe = cJSON_GetObjectItem(json_input, "pppoe");
if (pppoe != NULL && cJSON_IsObject(pppoe))
{
    cJSON *username = cJSON_GetObjectItem(pppoe, "username");
    if (username != NULL && cJSON_IsString(username))
    {
        snprintf(output->pppoe.username, sizeof(output->pppoe.username), "%s", username->valuestring);
    }
    else
    {
        log_error("Key 'username' not found in pppoe");
        return ERROR_INVALID_USERNAME;
    }

    cJSON *password = cJSON_GetObjectItem(pppoe, "password");
    if (password != NULL && cJSON_IsString(password))
    {
        snprintf(output->pppoe.password, sizeof(output->pppoe.password), "%s", password->valuestring);
    }
    else
    {
        log_error("Key 'password' not found in pppoe");
        return ERROR_INVALID_PASSWORD;
    }
}
else
{
    log_error("Key 'pppoe' not found or not an object");
    return ERROR_INVALID_JSON;
}
cJSON *ipv4 = cJSON_GetObjectItem(json_input, "ipv4");
if (ipv4 != NULL && cJSON_IsObject(ipv4))
{
    cJSON *ip = cJSON_GetObjectItem(ipv4, "ip");
    if (ip != NULL && cJSON_IsString(ip))
    {
        snprintf(output->ipv4.ip, sizeof(output->ipv4.ip), "%s", ip->valuestring);
        error_t err = is_valid_ipv4(output->ipv4.ip);
        if (err != ERROR_NONE)
        {
            log_error("Invalid IPv4 address: %s", output->ipv4.ip);
            return err;
        }
    }
    else
    {
        log_error("Key 'ip' not found in ipv4");
        return ERROR_INVALID_IP;
    }

    cJSON *mask = cJSON_GetObjectItem(ipv4, "mask");
    if (mask != NULL && cJSON_IsString(mask))
    {
        snprintf(output->ipv4.mask, sizeof(output->ipv4.mask), "%s", mask->valuestring);
        error_t err = is_valid_ipv4(output->ipv4.mask);
        if (err != ERROR_NONE)
        {
            log_error("Invalid IPv4 mask: %s", output->ipv4.mask);
            return err;
        }
    }
    else
    {
        log_error("Key 'mask' not found in ipv4");
        return ERROR_INVALID_MASK;
    }

    cJSON *gw = cJSON_GetObjectItem(ipv4, "gw");
    if (gw != NULL && cJSON_IsString(gw))
    {
        snprintf(output->ipv4.gw, sizeof(output->ipv4.gw), "%s", gw->valuestring);
        error_t err = is_valid_ipv4(output->ipv4.gw);
        if (err != ERROR_NONE)
        {
            log_error("Invalid IPv4 gateway: %s", output->ipv4.gw);
            return err;
        }
    }
    else
    {
        log_error("Key 'gw' not found in ipv4");
        return ERROR_INVALID_GW;
    }

    cJSON *dns = cJSON_GetObjectItem(ipv4, "dns");
    if (dns != NULL && cJSON_IsArray(dns))
    {
        output->ipv4.dns_count = 0;
        cJSON *dns_item = dns->child;
        while (dns_item != NULL && output->ipv4.dns_count < MAX_DNS_SERVERS)
        {
            if (cJSON_IsString(dns_item))
            {
                snprintf(output->ipv4.dns[output->ipv4.dns_count], sizeof(output->ipv4.dns[output->ipv4.dns_count]), "%s", dns_item->valuestring);
                error_t err = is_valid_ipv4(output->ipv4.dns[output->ipv4.dns_count]);
                if (err != ERROR_NONE)
                {
                    log_error("Invalid IPv4 DNS: %s", output->ipv4.dns[output->ipv4.dns_count]);
                    return err;
                }
                output->ipv4.dns_count++;
            }
            dns_item = dns_item->next;
        }

        return ERROR_NONE;
    }
    else
    {
        log_error("Key 'dns' not found in ipv4");
        return ERROR_INVALID_JSON;
    }
}
else
{
    log_error("Key 'ipv4' not found or not an object");
    return ERROR_INVALID_JSON;
}
cJSON *ipv6 = cJSON_GetObjectItem(json_input, "ipv6");
if (ipv6 != NULL && cJSON_IsObject(ipv6))
{
    cJSON *gw = cJSON_GetObjectItem(ipv6, "gw");
    if (gw != NULL && cJSON_IsString(gw))
    {
        snprintf(output->ipv6.gw, sizeof(output->ipv6.gw), "%s", gw->valuestring);
        error_t err = is_valid_ipv6(output->ipv6.gw);
        if (err != ERROR_NONE)
        {
            log_error("Invalid IPv6 gateway: %s", output->ipv6.gw);
            return err;
        }
    }
    else
    {
        log_error("Key 'gw' not found in ipv6");
        return ERROR_INVALID_GW;
    }

    cJSON *dns = cJSON_GetObjectItem(ipv6, "dns");
    if (dns != NULL && cJSON_IsArray(dns))
    {
        output->ipv6.dns_count = 0;
        cJSON *dns_item = dns->child;
        while (dns_item != NULL && output->ipv6.dns_count < MAX_DNS_SERVERS)
        {
            if (cJSON_IsString(dns_item))
            {
                snprintf(output->ipv6.dns[output->ipv6.dns_count], sizeof(output->ipv6.dns[output->ipv6.dns_count]), "%s", dns_item->valuestring);
                error_t err = is_valid_ipv6(output->ipv6.dns[output->ipv6.dns_count]);
                if (err != ERROR_NONE)
                {
                    log_error("Invalid IPv6 DNS: %s", output->ipv6.dns[output->ipv6.dns_count]);
                    return err;
                }
                output->ipv6.dns_count++;
            }
            dns_item = dns_item->next;
        }
    }
    else
    {
        log_error("Key 'dns' not found in ipv4");
        return ERROR_INVALID_JSON;
    }

    cJSON *alloc = cJSON_GetObjectItem(ipv6, "alloc");
    if (alloc != NULL && cJSON_IsString(alloc))
    {
        for (int i = 0; i < IPV4_SIZE; i++)
        {
            if (strcmp(alloc->valuestring, valid_ipv4_alloc[i]) == 0)
            {
                output->ipv4.alloc = (wan_ipv4_alloc_t)i;
                break;
            }
        }
        if (output->ipv4.alloc >= IPV4_SIZE)
        {
            log_error("Invalid IPv4 alloc field in JSON");
            return ERROR_INVALID_ALLOC_MODE;
        }
    }
    else
    {
        log_error("Key 'alloc' not found in ipv6");
        return ERROR_INVALID_JSON;
    }

    cJSON *prefix = cJSON_GetObjectItem(ipv6, "prefix");
    if (prefix != NULL && cJSON_IsObject(prefix))
    {
        cJSON *prefix_value = cJSON_GetObjectItem(prefix, "value");
        if (prefix_value != NULL && cJSON_IsString(prefix_value))
        {
            snprintf(output->ipv6.prefix.prefix_value, sizeof(output->ipv6.prefix.prefix_value), "%s", prefix_value->valuestring);
        }
        else
        {
            log_error("Key 'value' not found in prefix");
            return ERROR_INVALID_PREFIX;
        }

        cJSON *primary_time = cJSON_GetObjectItem(prefix, "primary_time");
        if (primary_time != NULL && cJSON_IsString(primary_time))
        {
            snprintf(output->ipv6.prefix.primary_time, sizeof(output->ipv6.prefix.primary_time), "%s", primary_time->valuestring);
        }
        else
        {
            log_error("Key 'primary_time' not found in prefix");
            return ERROR_INVALID_PRIMARY_TIME;
        }

        cJSON *lease_time = cJSON_GetObjectItem(prefix, "lease_time");
        if (lease_time != NULL && cJSON_IsString(lease_time))
        {
            snprintf(output->ipv6.prefix.lease_time, sizeof(output->ipv6.prefix.lease_time), "%s", lease_time->valuestring);
        }
        else
        {
            log_error("Key 'lease_time' not found in prefix");
            return ERROR_INVALID_LEASE_TIME;
        }

        cJSON *mode = cJSON_GetObjectItem(prefix, "mode");
        if (mode != NULL && cJSON_IsString(mode))
        {
            for (int i = 0; i < PREFIX_SIZE; i++)
            {
                if (strcmp(mode->valuestring, valid_prefix_mode[i]) == 0)
                {
                    output->ipv6.prefix.prefix_mode = (wan_prefix_mode_t)i;
                    break;
                }
            }
            if (output->ipv6.prefix.prefix_mode >= PREFIX_SIZE)
            {
                log_error("Invalid prefix mode field in JSON");
                return ERROR_INVALID_PREFIX;
            }
        }
        else
        {
            log_error("Key 'mode' not found in prefix");
            return ERROR_INVALID_JSON;
        }
    }
    else
    {
        log_error("Key 'prefix' not found or not an object");
        return ERROR_INVALID_JSON;
    }
    cJSON *alloc = cJSON_GetObjectItem(ipv6, "alloc");
    if (alloc != NULL && cJSON_IsString(alloc))
    {
        for (int i = 0; i < IPV6_SIZE; i++)
        {
            if (strcmp(alloc->valuestring, valid_ipv6_alloc[i]) == 0)
            {
                output->ipv6.alloc = (wan_ipv6_alloc_t)i;
                break;
            }
        }
        if (output->ipv6.alloc >= IPV6_SIZE)
        {
            log_error("Invalid IPv6 alloc field in JSON");
            return ERROR_INVALID_ALLOC_MODE;
        }
    }
    else
    {
        log_error("Key 'alloc' not found in ipv6");
        return ERROR_INVALID_JSON;
    }
}
else
{
    log_error("Key 'ipv6' not found or not an object");
    return ERROR_INVALID_JSON;
}
return ERROR_NONE;