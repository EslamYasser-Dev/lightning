/* This file was generated by generate-wire.py */
/* Do not modify this file! Modify the .csv file it was generated from. */
/* Original template can be found at tools/gen/impl_template */

#include <gossipd/gossip_store_wiregen.h>
#include <assert.h>
#include <ccan/array_size/array_size.h>
#include <ccan/mem/mem.h>
#include <ccan/tal/str/str.h>
#include <common/utils.h>
#include <stdio.h>

#ifndef SUPERVERBOSE
#define SUPERVERBOSE(...)
#endif

/* gossip_store messages: messages persisted in the gossip_store */
/* We store raw messages here */
/* 256/257/258. */

const char *gossip_store_wire_name(int e)
{
	static char invalidbuf[sizeof("INVALID ") + STR_MAX_CHARS(e)];

	switch ((enum gossip_store_wire)e) {
	case WIRE_GOSSIP_STORE_CHANNEL_AMOUNT: return "WIRE_GOSSIP_STORE_CHANNEL_AMOUNT";
	case WIRE_GOSSIP_STORE_PRIVATE_CHANNEL: return "WIRE_GOSSIP_STORE_PRIVATE_CHANNEL";
	case WIRE_GOSSIP_STORE_PRIVATE_UPDATE: return "WIRE_GOSSIP_STORE_PRIVATE_UPDATE";
	case WIRE_GOSSIP_STORE_DELETE_CHAN: return "WIRE_GOSSIP_STORE_DELETE_CHAN";
	case WIRE_GOSSIPD_LOCAL_ADD_CHANNEL_OBS: return "WIRE_GOSSIPD_LOCAL_ADD_CHANNEL_OBS";
	}

	snprintf(invalidbuf, sizeof(invalidbuf), "INVALID %i", e);
	return invalidbuf;
}

bool gossip_store_wire_is_defined(u16 type)
{
	switch ((enum gossip_store_wire)type) {
	case WIRE_GOSSIP_STORE_CHANNEL_AMOUNT:;
	case WIRE_GOSSIP_STORE_PRIVATE_CHANNEL:;
	case WIRE_GOSSIP_STORE_PRIVATE_UPDATE:;
	case WIRE_GOSSIP_STORE_DELETE_CHAN:;
	case WIRE_GOSSIPD_LOCAL_ADD_CHANNEL_OBS:;
	      return true;
	}
	return false;
}





/* WIRE: GOSSIP_STORE_CHANNEL_AMOUNT */
/* This always follows the channel_announce / private_announce */
u8 *towire_gossip_store_channel_amount(const tal_t *ctx, struct amount_sat satoshis)
{
	u8 *p = tal_arr(ctx, u8, 0);

	towire_u16(&p, WIRE_GOSSIP_STORE_CHANNEL_AMOUNT);
	towire_amount_sat(&p, satoshis);

	return memcheck(p, tal_count(p));
}
bool fromwire_gossip_store_channel_amount(const void *p, struct amount_sat *satoshis)
{
	const u8 *cursor = p;
	size_t plen = tal_count(p);

	if (fromwire_u16(&cursor, &plen) != WIRE_GOSSIP_STORE_CHANNEL_AMOUNT)
		return false;
 	*satoshis = fromwire_amount_sat(&cursor, &plen);
	return cursor != NULL;
}

/* WIRE: GOSSIP_STORE_PRIVATE_CHANNEL */
/* Mimics a channel_announce */
u8 *towire_gossip_store_private_channel(const tal_t *ctx, struct amount_sat satoshis, const u8 *announcement)
{
	u16 len = tal_count(announcement);
	u8 *p = tal_arr(ctx, u8, 0);

	towire_u16(&p, WIRE_GOSSIP_STORE_PRIVATE_CHANNEL);
	towire_amount_sat(&p, satoshis);
	towire_u16(&p, len);
	towire_u8_array(&p, announcement, len);

	return memcheck(p, tal_count(p));
}
bool fromwire_gossip_store_private_channel(const tal_t *ctx, const void *p, struct amount_sat *satoshis, u8 **announcement)
{
	u16 len;

	const u8 *cursor = p;
	size_t plen = tal_count(p);

	if (fromwire_u16(&cursor, &plen) != WIRE_GOSSIP_STORE_PRIVATE_CHANNEL)
		return false;
 	*satoshis = fromwire_amount_sat(&cursor, &plen);
 	len = fromwire_u16(&cursor, &plen);
 	// 2nd case announcement
	*announcement = len ? tal_arr(ctx, u8, len) : NULL;
	fromwire_u8_array(&cursor, &plen, *announcement, len);
	return cursor != NULL;
}

/* WIRE: GOSSIP_STORE_PRIVATE_UPDATE */
u8 *towire_gossip_store_private_update(const tal_t *ctx, const u8 *update)
{
	u16 len = tal_count(update);
	u8 *p = tal_arr(ctx, u8, 0);

	towire_u16(&p, WIRE_GOSSIP_STORE_PRIVATE_UPDATE);
	towire_u16(&p, len);
	towire_u8_array(&p, update, len);

	return memcheck(p, tal_count(p));
}
bool fromwire_gossip_store_private_update(const tal_t *ctx, const void *p, u8 **update)
{
	u16 len;

	const u8 *cursor = p;
	size_t plen = tal_count(p);

	if (fromwire_u16(&cursor, &plen) != WIRE_GOSSIP_STORE_PRIVATE_UPDATE)
		return false;
 	len = fromwire_u16(&cursor, &plen);
 	// 2nd case update
	*update = len ? tal_arr(ctx, u8, len) : NULL;
	fromwire_u8_array(&cursor, &plen, *update, len);
	return cursor != NULL;
}

/* WIRE: GOSSIP_STORE_DELETE_CHAN */
u8 *towire_gossip_store_delete_chan(const tal_t *ctx, const struct short_channel_id *scid)
{
	u8 *p = tal_arr(ctx, u8, 0);

	towire_u16(&p, WIRE_GOSSIP_STORE_DELETE_CHAN);
	towire_short_channel_id(&p, scid);

	return memcheck(p, tal_count(p));
}
bool fromwire_gossip_store_delete_chan(const void *p, struct short_channel_id *scid)
{
	const u8 *cursor = p;
	size_t plen = tal_count(p);

	if (fromwire_u16(&cursor, &plen) != WIRE_GOSSIP_STORE_DELETE_CHAN)
		return false;
 	fromwire_short_channel_id(&cursor, &plen, scid);
	return cursor != NULL;
}

/* WIRE: GOSSIPD_LOCAL_ADD_CHANNEL_OBS */
/* FIXME: Here for COMPAT with v0.9.0 and before only. */
u8 *towire_gossipd_local_add_channel_obs(const tal_t *ctx, const struct short_channel_id *short_channel_id, const struct node_id *remote_node_id, struct amount_sat satoshis, const u8 *features)
{
	u16 flen = tal_count(features);
	u8 *p = tal_arr(ctx, u8, 0);

	towire_u16(&p, WIRE_GOSSIPD_LOCAL_ADD_CHANNEL_OBS);
	towire_short_channel_id(&p, short_channel_id);
	towire_node_id(&p, remote_node_id);
	towire_amount_sat(&p, satoshis);
	towire_u16(&p, flen);
	towire_u8_array(&p, features, flen);

	return memcheck(p, tal_count(p));
}
bool fromwire_gossipd_local_add_channel_obs(const tal_t *ctx, const void *p, struct short_channel_id *short_channel_id, struct node_id *remote_node_id, struct amount_sat *satoshis, u8 **features)
{
	u16 flen;

	const u8 *cursor = p;
	size_t plen = tal_count(p);

	if (fromwire_u16(&cursor, &plen) != WIRE_GOSSIPD_LOCAL_ADD_CHANNEL_OBS)
		return false;
 	fromwire_short_channel_id(&cursor, &plen, short_channel_id);
 	fromwire_node_id(&cursor, &plen, remote_node_id);
 	*satoshis = fromwire_amount_sat(&cursor, &plen);
 	flen = fromwire_u16(&cursor, &plen);
 	// 2nd case features
	*features = flen ? tal_arr(ctx, u8, flen) : NULL;
	fromwire_u8_array(&cursor, &plen, *features, flen);
	return cursor != NULL;
}
// SHA256STAMP:c366132d32c26c52e94d122eb16df0b04f9a28bc8eaa437d11565da35ebdbc09
