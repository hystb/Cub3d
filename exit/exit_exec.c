#include "../includes/exec.h"

void	free_exec_struct(t_player *p)
{
	if (p)
	{
		ft_free(p->position);
		if (p->rcast)
		{
			ft_free(p->rcast->hor);
			ft_free(p->rcast->ver);
			ft_free(p->rcast->imgdata);
			ft_free(p->rcast);
		}
		ft_free(p);
	}
}