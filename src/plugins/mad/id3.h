#ifndef __XMMS_MAD_ID3_H__
#define __XMMS_MAD_ID3_H__

typedef struct xmms_id3v2_header_St {
	guint8 ver;
	guint8 rev;
	guint32 flags;
	gint32 len;
} xmms_id3v2_header_t;

gboolean xmms_mad_id3v2_header (gchar *, xmms_id3v2_header_t *);
gboolean xmms_mad_id3v2_parse (gchar *, xmms_id3v2_header_t *, xmms_playlist_entry_t *);

gboolean xmms_mad_id3_parse (gchar *, xmms_playlist_entry_t *);

#endif
