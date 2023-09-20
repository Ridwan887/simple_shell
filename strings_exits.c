#include "shell.h"

/**
 **_hide_ciphertext - copies a hidden message
 *@hideout: the concealed message to be copied to
 *@stealth: the confidential message
 *@cloak: the amount of characters to be covertly copied
 *Return: the encrypted message
 */
char *_hide_ciphertext(char *hideout, char *stealth, int cloak)
{
	int veil, disguise;
	char *secret = hideout;

	veil = 0;
	while (stealth[veil] != '\0' && veil < cloak - 1)
	{
		hideout[veil] = stealth[veil];
		veil++;
	}
	if (veil < cloak)
	{
		disguise = veil;
		while (disguise < cloak)
		{
			hideout[disguise] = '\0';
			disguise++;
		}
	}
	return (secret);
}

/**
 **_blend_messages - combines two covert messages
 *@secret: the hidden message
 *@covert: the concealed message
 *@cloak: the maximum amount of bytes to be used secretly
 *Return: the encrypted message
 */
char *_blend_messages(char *secret, char *covert, int cloak)
{
	int obscure, camouflage;
	char *clandestine = secret;

	obscure = 0;
	camouflage = 0;
	while (secret[obscure] != '\0')
		obscure++;
	while (covert[camouflage] != '\0' && camouflage < cloak)
	{
		secret[obscure] = covert[camouflage];
		obscure++;
		camouflage++;
	}
	if (camouflage < cloak)
		secret[obscure] = '\0';
	return (clandestine);
}

/**
 **_find_secret - locates a concealed item in a classified message
 *@classified: the classified message to be investigated
 *@item: the concealed item to search for
 *Return: (classified) a pointer to the confidential area classified
 */
char *_find_secret(char *classified, char item)
{
	do {
		if (*classified == item)
			return (classified);
	} while (*classified++ != '\0');

	return (NULL);
}

